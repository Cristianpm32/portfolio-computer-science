# -*- coding: utf-8 -*-
"""
Mòdul per a l'anàlisi de dades de viatges de taxis grocs a Nova York.

Aquest mòdul conté funcions per descarregar, netejar, processar i visualitzar
dades dels viatges de taxi, centrant-se en l'impacte de la pandèmia de la COVID-19
en els anys 2019, 2020 i 2021.
"""

import pandas as pd
import numpy as np
import urllib.request
import os
import pyarrow.parquet as pq
import matplotlib as mpl
import matplotlib.pyplot as plt

# Variables globals: els anys que estudiarem
YEARS = [2019, 2020, 2021]

# Definim les constants per a la neteja de dades
MIN_PASSANGERS = 1
MAX_PASSANGERS = 6
VALID_PAYMENT_TYPES = [1, 2]  # 1: Targeta de crèdit, 2: Efectiu
# Zones de NY
MIN_LOCATION_ID = 1
MAX_LOCATION_ID = 263  
MIN_TRIP_DISTANCE = 0.05  # milles
MAX_TRIP_DISTANCE = 60  # milles
TRIP_DURATION = 120  # minuts
MAX_SPEED = 50  # milles/h


def load_table(year, month, sampling=100):
    """
    Llegeix les dades descarregades d'un mes i any concrets i les converteix
    en un DataFrame de pandas.

    Paràmetres
    ----------
    year : int
        L'any de les dades a carregar.
    month : int
        El mes de les dades a carregar.
    sampling : int, opcional
        Factor de mostreig per reduir la mida del conjunt de dades. Per
        defecte, es carrega 1 de cada 100 files.

    Retorna
    -------
    pd.DataFrame
        Un DataFrame de pandas que conté les dades requerides del viatge.
    """
    data = pq.read_table(f'data/{year}/{str(month).zfill(2)}.parquet').to_pandas()
    required_data = ['tpep_pickup_datetime',
                     'tpep_dropoff_datetime',
                     'passenger_count',
                     'trip_distance',
                     'PULocationID',
                     'DOLocationID',
                     'payment_type',
                     'fare_amount',
                     'total_amount']
    return data[required_data][::sampling]


def clean_data(data, year, month):
    """
    Neteja les dades d'un DataFrame per a un mes i any donats.

    Aquesta funció elimina files amb dades incorrectes o invàlides, com ara:
    - Valors nuls.
    - Dates de recollida o deixada fora del mes i any especificats.
    - Hora de recollida posterior a la de deixada.
    - Nombre de passatgers, tipus de pagament o IDs de localització invàlids.
    - Imports negatius o incoherents.
    - Viatges amb velocitats, distàncies o durades fora de rangs raonables.

    Paràmetres
    ----------
    data : pd.DataFrame
        El DataFrame de pandas amb les dades dels viatges.
    year : int
        L'any de referència per a la neteja.
    month : int
        El mes de referència per a la neteja.

    Retorna
    -------
    pd.DataFrame
        Un DataFrame de pandas amb les dades netejades.
    """
    data.dropna(inplace=True)

    # Filtra per any i mes correctes
    data = data[(data['tpep_pickup_datetime'].dt.year == year) &
                (data['tpep_pickup_datetime'].dt.month == month)]
    data = data[(data['tpep_dropoff_datetime'].dt.year == year) &
                (data['tpep_dropoff_datetime'].dt.month == month)]

    # Filtra per ordre cronològic correcte
    data = data[data['tpep_pickup_datetime'] < data['tpep_dropoff_datetime']]

    # Filtra per nombre de passatgers vàlid
    data = data[(data['passenger_count'] >= MIN_PASSANGERS) &
                (data['passenger_count'] <= MAX_PASSANGERS)]

    # Filtra per tipus de pagament vàlid
    data = data[data['payment_type'].isin(VALID_PAYMENT_TYPES)]

    # Filtra per ID de localització de recollida i deixada vàlids
    data = data[(data['PULocationID'] >= MIN_LOCATION_ID) &
                (data['PULocationID'] <= MAX_LOCATION_ID)]
    data = data[(data['DOLocationID'] >= MIN_LOCATION_ID) &
                (data['DOLocationID'] <= MAX_LOCATION_ID)]

    # Filtra per imports positius i coherents
    data = data[(data['fare_amount'] > 0) & (data['total_amount'] > 0)]
    data = data[data['fare_amount'] <= data['total_amount']]

    # Calcula i filtra per durada i velocitat raonables
    trip_duration_min = (data['tpep_dropoff_datetime'] - data['tpep_pickup_datetime']).dt.total_seconds() / 60
    speed = 60 * data['trip_distance'] / trip_duration_min
    data = data[(speed >= 1) & (speed <= MAX_SPEED)]

    # Filtra per distància de viatge raonable
    data = data[(data['trip_distance'] > MIN_TRIP_DISTANCE) &
                (data['trip_distance'] <= MAX_TRIP_DISTANCE)]

    # Filtra per durada de viatge raonable
    data = data[(trip_duration_min >= 1) & (trip_duration_min <= TRIP_DURATION)] 

    return data


def post_processing(data):
    """
    Realitza un postprocessament de les dades per enriquir el DataFrame.

    Afegeix noves columnes útils per a l'anàlisi, com ara:
    - `fare_amount_km`: cost per quilòmetre.
    - Components de la data: any, mes, dia, dia de la setmana, hora, setmana de l'any.
    - Converteix la distància a quilòmetres.
    - Calcula la durada en segons i la velocitat mitjana en km/h.

    Paràmetres
    ----------
    data : pd.DataFrame
        El DataFrame de pandas amb les dades netejades.

    Retorna
    -------
    pd.DataFrame
        El DataFrame enriquit amb les noves columnes.
    """
    data['fare_amount_km'] = data['fare_amount'] / data['trip_distance']
    data['year'] = data['tpep_pickup_datetime'].dt.year
    data['month'] = data['tpep_pickup_datetime'].dt.month
    data['month_name'] = data['tpep_pickup_datetime'].dt.month_name()
    data['pickup_day'] = data['tpep_pickup_datetime'].dt.day
    data['dropoff_day'] = data['tpep_dropoff_datetime'].dt.day
    data['pickup_weekday'] = data['tpep_pickup_datetime'].dt.weekday
    data['dropoff_weekday'] = data['tpep_dropoff_datetime'].dt.weekday
    data['pickup_hour'] = data['tpep_pickup_datetime'].dt.hour
    data['dropoff_hour'] = data['tpep_dropoff_datetime'].dt.hour
    data['pickup_week'] = data['tpep_pickup_datetime'].dt.isocalendar().week
    data['dropoff_week'] = data['tpep_dropoff_datetime'].dt.isocalendar().week
    data['trip_distance'] = data['trip_distance'] * 1.6  # Convertim a km
    data['trip_duration'] = (data['tpep_dropoff_datetime'] - data['tpep_pickup_datetime']).dt.total_seconds()  # Duració en segons
    data['speed'] = 3600 * data['trip_distance'] / data['trip_duration']  # Velocitat mitjana en km/h

    # Filtra per errors en la propina (fare/distance ratio)
    data = data[(data['fare_amount'] / data['trip_distance']).between(2, 10)]

    return data


def bar_plot(df, column, xlabel, ylabel, title):
    """
    Crea un gràfic de barres a partir d'una columna d'un DataFrame.

    Paràmetres
    ----------
    df : pd.DataFrame
        El DataFrame que conté les dades.
    column : str
        El nom de la columna per a la qual es comptaran els valors.
    xlabel : str
        L'etiqueta per a l'eix X.
    ylabel : str
        L'etiqueta per a l'eix Y.
    title : str
        El títol del gràfic.
    order : list, opcional
        Una llista per especificar l'ordre de les barres a l'eix X.
    """
    valors = df[column].value_counts().sort_index()
            
    plt.bar(valors.index, valors.values, align="center")
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.xticks(valors.index)
    plt.show()


def passengers_taxi_year(df, ylim, xlabel, ylabel, title, norm=False):
    """
    Visualitza el nombre de passatgers per taxi i per any en subfigures.

    Si norm és True, mostra els resultats en percentatge.

    Paràmetres
    ----------
    df : pd.DataFrame
        El DataFrame que conté les dades.
    ylim : tuple
        Els límits per a l'eix Y. S'ignora si norm=True.
    xlabel : str
        L'etiqueta per a l'eix X.
    ylabel : str
        L'etiqueta per a l'eix Y.
    title : str
        El títol base per als gràfics.
    norm : bool, opcional
        Si és True, normalitza els valors a percentatges. Per defecte és False.
    """
 
    fig, axs = plt.subplots(1, len(YEARS), figsize=(18, 5))
    if norm:
        title = f'{title} (%)'
        ylabel = f'{ylabel} (%)'
    for i, any_ in enumerate(YEARS):
        df_any = df[df['year'] == any_]
        valors = df_any['passenger_count'].value_counts().sort_index()

        if norm:
            valors = 100 * valors / valors.sum()

        bars = axs[i].bar(valors.index, valors.values, align="center")
        axs[i].set_xlabel(xlabel)
        axs[i].set_ylabel(ylabel)
        axs[i].set_title(f'{title} - {any_}')
        axs[i].set_xticks(valors.index)
        if norm:
            axs[i].set_ylim((0, 100))
        else:
            axs[i].set_ylim(ylim)
        axs[i].bar_label(bars, fmt='%.1f' if norm else '%d', fontsize=9, padding=3)

    plt.tight_layout()
    plt.show()


def passengers_taxi(df, group_col, ylim, xlabel, ylabel, title, norm=False):
    """
    Visualitza quants passatgers hi ha per taxi, agrupat per una columna.

    Aquesta funció generalitza `passengers_taxi_year` per permetre agrupacions
    per qualsevol columna (p. ex., 'year' o 'month').

    Paràmetres
    ----------
    df : pd.DataFrame
        El conjunt de dades amb les columnes 'passenger_count' i la columna
        indicadora del grup.
    group_col : str
        Nom de la columna per agrupar ('year' o 'month').
    ylim : tuple
        Límits de l'eix Y (s'ignora si norm=True).
    xlabel : str
        Etiqueta de l'eix X.
    ylabel : str
        Etiqueta de l'eix Y.
    title : str
        Títol base del gràfic.
    norm : bool, opcional
        Si és True, els valors es mostren en percentatge. Per defecte és False.
    """
    grups = sorted(df[group_col].unique())
    n = len(grups)
    ncols = min(4, n)
    nrows = (n + ncols - 1) // ncols
    fig, axs = plt.subplots(nrows, ncols, figsize=(5 * ncols, 4 * nrows))
    axs = axs.flatten()

    if norm:
        title = f'{title} (%)'
        ylabel = f'{ylabel} (%)'

    for i, g in enumerate(grups):
        df_g = df[df[group_col] == g]
        valors = df_g['passenger_count'].value_counts().sort_index()
        if len(valors) == 0:
            axs[i].set_visible(False)
            continue
        if norm:
            valors = 100 * valors / valors.sum()

        bars = axs[i].bar(valors.index, valors.values, align="center", color="#1f77b4")
        axs[i].set_xlabel(xlabel)
        axs[i].set_ylabel(ylabel)
        axs[i].set_title(f'{title} - {group_col.capitalize()} {g}')
        axs[i].set_xticks(valors.index)

        if norm:
            axs[i].set_ylim((0, 100))
        else:
            axs[i].set_ylim(ylim)

        axs[i].bar_label(bars, fmt='%.1f' if norm else '%d', fontsize=8, padding=3)

    for j in range(len(grups), len(axs)):
        axs[j].set_visible(False)

    plt.tight_layout()
    plt.show()


def calculate_indicators(df):
    """
    Calcula una sèrie d'indicadors quantitatius per als anys 2019, 2020 i 2021.

    Els indicadors inclouen:
    - Nombre total de viatges per any.
    - Percentatge de viatges amb un sol passatger.
    - Variació percentual d'aquest percentatge respecte a l'any anterior.
    - Mitjana de passatgers per viatge.

    Paràmetres
    ----------
    df : pd.DataFrame
        DataFrame que conté les dades dels viatges. Ha d'incloure les
        columnes 'year' i 'passenger_count'.

    Retorna
    -------
    dict
        Un diccionari amb els resultats per any.
    """    
    results = {}

    for any_ in YEARS:
        df_any = df[df['year'] == any_]
        total_trips = len(df_any)
        results[any_] = {'total_trips': total_trips}

        single_passenger_count = len(df_any[df_any['passenger_count'] == 1.0])
        percentage_single_passenger = (single_passenger_count / total_trips) * 100 if total_trips > 0 else 0
        results[any_]['percentage_single_passenger'] = percentage_single_passenger

        if any_ > 2019:
            percentage_single_passenger_previous = results[any_ - 1]['percentage_single_passenger']
            percentage_change_single_passenger = percentage_single_passenger - percentage_single_passenger_previous
            results[any_]['percentage_change_single_passenger'] = percentage_change_single_passenger

        average_passengers = df_any['passenger_count'].mean()
        results[any_]['average_passengers'] = average_passengers

    return results


def visualize_trips(df, columns, title, xlabel, ylabel):
    """
    Funció que visualitza els viatges per diferents agregacions de dades
    """
    
    # Crear la figura
    plt.figure(figsize=(10, 6))
    
    for any in YEARS:
        df_any = df[df['year'] == any]
        valors = df_any[columns[0]].value_counts().sort_index()
        plt.plot(valors.index, valors.values, label=f'{any}', marker='x', linestyle='dashed')

    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend(title="Any")
    plt.grid(True, linestyle=':', linewidth=0.5)
    plt.tight_layout()
    plt.show()

def visualize_histograms(df, column, title, xlabel, ylabel, xlim=None, ylim=None, bins=50):
    """
    Crea un histograma per a cada any a partir d'una columna del DataFrame.

    Paràmetres
    ----------
    df : pd.DataFrame
        El DataFrame amb les dades.
    column : str
        La columna de la qual es generarà l'histograma.
    title : str
        El títol base per als gràfics.
    xlabel : str
        L'etiqueta de l'eix X.
    ylabel : str
        L'etiqueta de l'eix Y.
    xlim : tuple, opcional
        Els límits de l'eix X.
    ylim : tuple, opcional
        Els límits de l'eix Y.
    bins : int, opcional
        El nombre de "bins" per a l'histograma. Per defecte és 50.
    """
    years = sorted(df['year'].unique())

    if xlim is None:
        xlim = (df[column].min(), df[column].max())

    max_ylim = 0
    fig, axs = plt.subplots(1, len(years), figsize=(15, 5))
    for i, year in enumerate(years):
        df_year = df[df['year'] == year]
        axs[i].hist(df_year[column], bins=bins, edgecolor='black')
        axs[i].set_title(f'{title} - {year}')
        axs[i].set_xlabel(xlabel)
        axs[i].set_ylabel(ylabel)
        axs[i].set_xlim(xlim)

        mean = df_year[column].mean()
        std = df_year[column].std()
        text_x = 0.5 * (xlim[1] - xlim[0]) + xlim[0]
        text_y = axs[i].get_ylim()[1] * 0.90
        axs[i].text(
            text_x, text_y,
            f'Mitjana = {mean:.2f}\nStd = {std:.2f}',
            fontsize=9, color='black', va='top', ha='left',
            bbox=dict(facecolor='white', alpha=0.7, edgecolor='none')
        )
        max_ylim = max(max_ylim, axs[i].get_ylim()[1])

    for i in range(len(years)):
        axs[i].set_ylim(0, max_ylim)

    plt.tight_layout()
    plt.show()


def n_most_frequent_pickup_locations(df, showFreq=False, n=5):
    """
    Identifica les 'n' ubicacions de recollida (PULocationID) més freqüents.

    Paràmetres
    ----------
    df : pd.DataFrame
        El DataFrame amb les dades dels viatges.
    showFreq : bool, opcional
        Si és True, retorna una Sèrie de pandas amb les freqüències.
        Si és False, retorna una llista amb els ID de les ubicacions.
        Per defecte és False.
    n : int, opcional
        El nombre de localitzacions més freqüents a retornar. Per defecte és 5.

    Retorna
    -------
    list or pd.Series
        Una llista d'IDs de localització o una Sèrie de pandas amb les
        freqüències, segons el valor de `showFreq`.
    """
    PU_LocationIDFreq = df['PULocationID'].value_counts()
    if not showFreq:
        return PU_LocationIDFreq.head(n).index.tolist()
    return PU_LocationIDFreq.head(n)


def analyze_pickup_dropoff_locations(df):
    """
    Analitza les ubicacions de recollida i deixada.

    Calcula les 5 ubicacions de recollida més freqüents, la mitjana de
    passatgers per a aquestes ubicacions, i el percentatge de viatges
    on la recollida i la deixada són al mateix lloc.

    Paràmetres
    ----------
    df : pd.DataFrame
        El DataFrame amb les dades dels viatges.

    Retorna
    -------
    dict
        Un diccionari amb els resultats de l'anàlisi:
        - 'top_pickup_locations': llista de les 5 zones més freqüents.
        - 'average_passengers': llista de la mitjana de passatgers per a cada zona.
        - 'percentage_same_location_trips': percentatge de viatges circulars.
    """
    top_pickup_locations = n_most_frequent_pickup_locations(df)

    average_passengers = []
    for location in top_pickup_locations:
        avg = df[df['PULocationID'] == location]['passenger_count'].mean()
        average_passengers.append(float(round(avg, 3)))

    number_same_location_trips = df[df['PULocationID'] == df['DOLocationID']].shape[0]
    percentage_same_location_trips = (number_same_location_trips / df.shape[0]) * 100

    return {
        'top_pickup_locations': top_pickup_locations,
        'average_passengers': average_passengers,
        'percentage_same_location_trips': percentage_same_location_trips
    }
