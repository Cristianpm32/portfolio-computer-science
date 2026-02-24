import pandas as pd
import mysql.connector
import os

schema_path = "f1db_tables_final.sql"

# Configuración de conexión
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="MatInfo-2021", # Poner la contraseña de tu db
)

# Crear un cursor para ejecutar consultas
cursor = conn.cursor()

# Leer el archivo SQL y ejecutar las consultas
with open(schema_path, "r", encoding="utf-8") as f:
    sql_script = f.read()

# Ejecutar múltiples sentencias separadas por ";"
for statement in sql_script.split(";"):
    stmt = statement.strip()
    if stmt:
        try:
            cursor.execute(stmt)
        except mysql.connector.Error as err:
            print(f"Error ejecutando sentencia: {stmt}\n{err}")

conn.commit()
cursor.close()
conn.close()

# Conectar a la base
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="MatInfo-2021",
    database="f1db"
)
cursor = conn.cursor()

# Esto sirve para limpiar la db, pero no es necesario
# era necesario para la prueba
'''
def truncate_all_tables():
    cursor.execute("SET FOREIGN_KEY_CHECKS = 0")
    for table in reversed(list(tables.keys())):
        cursor.execute(f"TRUNCATE TABLE {table}")
    cursor.execute("SET FOREIGN_KEY_CHECKS = 1")
    conn.commit()
    print("All tables truncated.")
'''

# Aquí se definen las columnas a escoger de cada tabla
tables = {
    "Constructors": ["constructorId", "name", "nationality"],
    "Drivers": ["driverId", "number", "code", "forename", "surname", "dob", "nationality"],
    "Circuits": ["circuitId", "name", "location", "country", "latitude", "longitude", "altitude"],
    "Races": ["raceId", "year", "round", "circuitId", "name", "date", "time"],
    "Results": ["resultId", "raceId", "driverId", "constructorId", "number", "grid", "position", "positionText", "points", "laps", "time", "milliseconds", "fastestLap", "fastestLapTime", "fastestLapSpeed"],
    "SprintResults": ["sprintResultId", "raceId", "driverId", "constructorId", "number", "grid", "position", "positionText", "points", "laps", "time", "milliseconds", "fastestLap", "fastestLapTime"],
    "LapTimes": ["raceId", "driverId", "lap", "position", "time", "milliseconds"],
    "ConstructorStandings": ["raceId", "constructorId", "points", "position", "positionText", "wins"],
    "DriverStandings": ["raceId", "driverId", "points", "position", "positionText", "wins"]
}

# Asocia nombre de archivo con tabla, para facilitar la lectura
file_map = {
    "Drivers": "drivers.csv",
    "Constructors": "constructors.csv",
    "Circuits": "circuits.csv",
    "Races": "races.csv",
    "Results": "results.csv",
    "SprintResults": "sprint_results.csv",
    "LapTimes": "lap_times.csv",
    "ConstructorStandings": "constructor_standings.csv",
    "DriverStandings": "driver_standings.csv"
}

# Se puede quitar
#truncate_all_tables()

# Procesar cada tabla
for table, valid_cols in tables.items():
    # Obtener el nombre del archivo correspondiente
    data_folder = "data"
    file_name = os.path.join(data_folder, file_map.get(table))

    # Comprobar si el archivo existe
    if not os.path.exists(file_name):
        print(f"Archivo no encontrado para {table}: {file_name}")
    
    print(f"Insertando en tabla {table} desde {file_name}...")

    # Leer el archivo CSV
    # Se añade el argumento na_values para manejar los valores nulos
    df = pd.read_csv(file_name, na_values='\\N')

    # Manejo especial para SprintResults: añadir sprintResultId , ya que de por sí no existe
    if table == "SprintResults" and "sprintResultId" not in df.columns:
        print("Añadiendo sprintResultId autogenerado...")
        df.insert(0, "sprintResultId", range(1, len(df) + 1))

    # Filtrar columnas válidas que existen en el archivo
    df = df[[col for col in valid_cols if col in df.columns]]

    # Eliminar duplicados por clave primaria (primera columna del schema)
    df = df.drop_duplicates(subset=df.columns[0], keep="first")

    # Reemplazar NaN con None (importante para MySQL)
    df = df.where(pd.notnull(df), None)

    # Construcción dinámica de columnas y placeholders
    insert_cols = df.columns.tolist()
    col_names = ', '.join([f"`{col}`" for col in insert_cols])
    placeholders = ', '.join(['%s'] * len(insert_cols))

    # Por cada fila
    for _, row in df.iterrows():

        # Crear una tupla con los valores de la fila
        row_tuple = tuple([None if pd.isna(val) else val for val in row])
        
        # Insertar en la tabla
        cursor.execute(
            f"INSERT INTO {table} ({col_names}) VALUES ({placeholders})",
            row_tuple
        )
    # Commit de la transacción
    conn.commit()
    print(f"Insertados {len(df)} registros en {table}")

# Cerrar la conexión
cursor.close()
# Cerrar la conexión
conn.close()
print("Todos los datos insertados correctamente.")

