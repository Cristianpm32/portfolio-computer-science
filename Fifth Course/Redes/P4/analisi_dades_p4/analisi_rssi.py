import pandas as pd
import matplotlib.pyplot as plt

# ==============================================================================
# CONFIGURACIÓ
# ==============================================================================
# Nom del fitxer descarregat de ThingSpeak
NOM_FITXER = 'dades_rssi.csv' 

def analitzar_dades():
    try:
        print(f"Llegint dades de {NOM_FITXER}...")
        
        # 1. Carreguem les dades
        # ThingSpeak exporta columnes com: created_at, entry_id, field1, etc.
        df = pd.read_csv(NOM_FITXER)
        
        # 2. Neteja de dades
        # L'RSSI està a la columna 'field1'. Ens assegurem que sigui numèric.
        # 'coerce' convertirà errors (textos no numèrics) en NaN
        df['field1'] = pd.to_numeric(df['field1'], errors='coerce')
        
        # Eliminem files buides o amb errors
        dades_netes = df.dropna(subset=['field1'])
        
        if len(dades_netes) == 0:
            print("Error: No s'han trobat dades vàlides a la columna 'field1'.")
            return

        # 3. Càlculs Estadístics (Segons Q4 de la pràctica)
        mitjana_rssi = dades_netes['field1'].mean()
        desviacio_estandard = dades_netes['field1'].std()
        minim = dades_netes['field1'].min()
        maxim = dades_netes['field1'].max()

        # 4. Mostrar Resultats
        print("\n" + "="*40)
        print("       RESULTATS DE L'ANÀLISI RSSI")
        print("="*40)
        print(f" Total mostres analitzades: {len(dades_netes)}")
        print(f" -> Mitjana (Mean):         {mitjana_rssi:.2f} dBm")
        print(f" -> Desviació Estàndard:    {desviacio_estandard:.2f} dB")
        print(f" -> Mínim senyal registrat: {minim} dBm")
        print(f" -> Màxim senyal registrat: {maxim} dBm")
        print("="*40 + "\n")

        # 5. Generar Gràfic (Histograma)
        plt.figure(figsize=(10, 6))
        plt.hist(dades_netes['field1'], bins=20, color='#4CAF50', edgecolor='black', alpha=0.7)
        
        plt.title('Distribució de la Potència del Senyal (RSSI)', fontsize=14)
        plt.xlabel('RSSI (dBm)', fontsize=12)
        plt.ylabel('Freqüència (Nombre de lectures)', fontsize=12)
        
        # Afegim una línia vertical per a la mitjana
        plt.axvline(mitjana_rssi, color='red', linestyle='dashed', linewidth=2, label=f'Mitjana: {mitjana_rssi:.2f} dBm')
        
        plt.legend()
        plt.grid(axis='y', alpha=0.5)
        plt.show()

    except FileNotFoundError:
        print(f"\n[ERROR]: No s'ha trobat el fitxer '{NOM_FITXER}'.")
        print("Assegura't de descarregar el CSV de ThingSpeak i posar-lo a la mateixa carpeta.")
    except Exception as e:
        print(f"\n[ERROR INESPERAT]: {e}")

if __name__ == "__main__":
    analitzar_dades()