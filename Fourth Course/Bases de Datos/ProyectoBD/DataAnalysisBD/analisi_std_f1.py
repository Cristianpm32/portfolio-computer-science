import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Cargar los datos
print("Cargando datos...")
pilots_df = pd.read_csv("data/Puntuacio_Pilots_BD.csv")
equips_df = pd.read_csv("data/Puntuacio_Equips_BD.csv")

# Definir función para asignar era por año
def assignar_era(year):
    if 1994 <= year <= 2008:
        return "Era de la Seguretat i l'Evolució Analògica"
    elif 2009 <= year <= 2013:
        return "Era de l'Eficiència Aerodinàmica"
    elif 2014 <= year <= 2016:
        return "Era Híbrida Inicial"
    elif 2017 <= year <= 2021:
        return "Era de la Màxima Càrrega Aerodinàmica"
    elif year >= 2022:
        return "Era del Nou Efecte Terra"
    else:
        return "Fora de període"

pilots_df["era"] = pilots_df["year"].apply(assignar_era)
equips_df["era"] = equips_df["year"].apply(assignar_era)

# Calcular puntos por carrera para cada piloto
pilots_df["puntos_por_carrera"] = pilots_df["total_points"] / pilots_df["num_races"]

# Calcular estadísticas para cada equipo por año
print("Calculando estadísticas por equipo...")
equips_stats = []

for year in sorted(pilots_df["year"].unique()):
    equipos_año = {}
    
    # Obtener equipos de este año
    teams_year = equips_df[equips_df["year"] == year]
    
    for constructor_id in teams_year["constructorId"]:
        # Obtener pilotos y puntos de este equipo y año
        pilotos_equipo = pilots_df[(pilots_df["year"] == year) & (pilots_df["constructorId"] == constructor_id)]
        
        # Puntos totales del equipo según equipos_df
        equipo_info = teams_year[teams_year["constructorId"] == constructor_id].iloc[0]
        puntos_equipo = equipo_info["total_points"]
        equipo_nombre = equipo_info["constructor_name"]
        
        # Si no hay pilotos registrados, continuar
        if len(pilotos_equipo) == 0:
            continue
        
        # Calcular el número total de carreras disputadas por el equipo
        total_carreras_pilotos = pilotos_equipo["num_races"].sum()
        # Dividir entre 2 ya que en cada GP participan 2 coches por equipo
        total_carreras_equipo = total_carreras_pilotos / 2
        
        # Calcular media ponderada de puntos por carrera
        # Cada piloto contribuye proporcionalmente al número de carreras disputadas
        suma_ponderada = sum(pilotos_equipo["puntos_por_carrera"] * pilotos_equipo["num_races"])
        media_puntos_por_carrera = suma_ponderada / total_carreras_pilotos
        
        # Calcular desviación estándar ponderada
        # Para cada piloto, calcular (pts_por_carrera - media)^2 * num_carreras
        suma_cuadrados = sum(
            (pilotos_equipo["puntos_por_carrera"] - media_puntos_por_carrera)**2 * pilotos_equipo["num_races"]
        )
        # Dividir entre el total de carreras para obtener la varianza ponderada
        varianza = suma_cuadrados / total_carreras_pilotos
        std_puntos_por_carrera = np.sqrt(varianza)
        
        # Calcular factor de penalización usando puntos por carrera
        if media_puntos_por_carrera > 0:
            factor_penalizacion = media_puntos_por_carrera / (std_puntos_por_carrera + media_puntos_por_carrera)
        else:
            factor_penalizacion = 1  # Sin penalización si no hay puntos
            
        # Calcular puntos ajustados
        puntos_ajustados = puntos_equipo * factor_penalizacion
        
        # Guardar estadísticas del equipo
        equipos_año[constructor_id] = {
            "nombre": equipo_nombre,
            "puntos_totales": puntos_equipo,
            "std_puntos_por_carrera": std_puntos_por_carrera,
            "media_puntos_por_carrera": media_puntos_por_carrera,
            "factor_penalizacion": factor_penalizacion,
            "puntos_ajustados": puntos_ajustados,
            "num_pilotos": len(pilotos_equipo),
            "total_carreras_pilotos": total_carreras_pilotos,
            "total_carreras_equipo": total_carreras_equipo
        }
        
        # Información de diagnóstico para 2024
        if year == 2006:
            print(f"\nEquipo: {equipo_nombre}")
            print("  Pilotos (puntos y carreras):")
            for _, p in pilotos_equipo.iterrows():
                print(f"    {p['forename']} {p['surname']}: {p['total_points']} pts en {p['num_races']} carreras = {p['puntos_por_carrera']:.2f} pts/carrera")
            print(f"  Total carreras con pilotos: {total_carreras_pilotos}, Total carreras equipo: {total_carreras_equipo:.1f}")
            print(f"  Media pts/carrera ponderada: {media_puntos_por_carrera:.2f}, Desv.Std ponderada: {std_puntos_por_carrera:.2f}")
            print(f"  Factor penalización: {factor_penalizacion:.4f}")
            print(f"  Puntos originales: {puntos_equipo}, Puntos ajustados: {puntos_ajustados:.1f}")
    
    # Calcular estadísticas de la temporada
    if equipos_año:
        puntos_ajustados_valores = [stats["puntos_ajustados"] for stats in equipos_año.values()]
        media_temporada = np.mean(puntos_ajustados_valores)
        std_temporada = np.std(puntos_ajustados_valores, ddof=0)
        
        # Calcular coeficiente de variación
        cv_temporada = std_temporada / media_temporada if media_temporada > 0 else 0
        
        equips_stats.append({
            "year": year,
            "era": assignar_era(year),
            "num_equipos": len(equipos_año),
            "media_puntos_ajustados": media_temporada,
            "std_puntos_ajustados": std_temporada,
            "cv": cv_temporada
        })

# Convertir a DataFrame
stats_df = pd.DataFrame(equips_stats)

# Calcular CV por era (media de los CV de cada año en la misma era)
print("\nCalculando CV por era...")
cv_por_era = stats_df.groupby("era")["cv"].mean().reset_index()

# Guardar resultados
stats_df.to_csv("cv_per_any_ponderado.csv", index=False)
cv_por_era.to_csv("cv_per_era_ponderado.csv", index=False)

print("\nResultados del CV por era:")
print(cv_por_era)

# Visualización
plt.figure(figsize=(12, 6))
plt.bar(cv_por_era["era"], cv_por_era["cv"])
plt.title("Coeficiente de Variación Medio por Era de F1 (Ponderado por Carreras)")
plt.ylabel("CV (Coeficiente de Variación)")
plt.xticks(rotation=45, ha="right")
plt.tight_layout()
plt.savefig("cv_per_era_ponderado.png")
print("Gráfico guardado como 'cv_per_era_ponderado.png'")


