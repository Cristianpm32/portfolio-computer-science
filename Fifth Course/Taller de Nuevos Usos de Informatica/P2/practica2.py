import pandas as pd
import numpy as np
import heapq



def top_movie(dataFrame: pd.DataFrame, usr: int) -> str:
    """
    Retorna el títol de la pel·lícula amb la puntuació més alta (i el MovieID més baix
    en cas d'empat) per a un usuari concret.

    :param dataFrame: DataFrame que conté totes les dades fusionades (ratings, users, movies).
    :param usr: ID de l'usuari (ja re-indexat) del qual es vol obtenir la pel·lícula millor puntuada.
    :return: Títol (string) de la pel·lícula més ben puntuada per l'usuari.
    """
    user_data = dataFrame[dataFrame['user_id'] == usr]
    # S'ordena per 'rating' descendent i 'movie_id' ascendent per complir l'ordre per defecte.
    best_movie_rating_row = user_data.sort_values(by=['rating', 'movie_id'], ascending=[False, True]).iloc[0]
    return best_movie_rating_row['title']

def build_counts_table(df: pd.DataFrame) -> pd.DataFrame:
    """
    Retorna un DataFrame on les columnes són els `movie_id` (re-indexats), les files
    `user_id` (re-indexats) i els valors són la valoració ('rating') que un usuari
    ha donat a una pel·lícula.

    :param df: DataFrame original (amb user_id i movie_id ja re-indexats).
    :return: DataFrame de recomptes (pivotat) amb usuaris per files i pel·lícules per columnes.
    """
    # L'enunciat original utilitzava aquesta línia, que re-indexa la columna 'movie_id'
    # en cada crida. Assumim que 'movie_id' i 'user_id' ja estan re-indexats globalment
    # abans de cridar aquesta funció, però mantenim la crida a .codes si es vol
    # garantir la re-indexació interna de movie_id, encara que no és necessari
    # si s'ha fet prèviament a tot el DataFrame 'data'.
    df['movie_id'] = pd.Categorical(df['movie_id']).codes
    df_counts = df.pivot(index='user_id', columns='movie_id', values='rating')
    return df_counts

def get_count(df: pd.DataFrame, user_id: int, movie_id: int) -> int:
    """
    Retorna la valoració que l'usuari 'user_id' ha donat a la 'movie_id'
    des d'un DataFrame pivotat.

    :param df: DataFrame retornat per `build_counts_table`.
    :param user_id: ID (re-indexat) de l'usuari.
    :param movie_id: ID (re-indexat) de la pel·lícula.
    :return: Valoració (int) de la pel·lícula per l'usuari. Retorna NaN si no existeix.
    """
    # Quan tenim df.index i df.columns amb les etiquetes (user_id i movie_id)
    return df.loc[user_id, movie_id] if pd.notna(df.loc[user_id, movie_id]) else 0

def distEuclid(x: np.ndarray, y: np.ndarray) -> float:
    """
    Retorna la distancia euclidiana entre dos vectors n-dimensionals.
    Implementació utilitzant funcions de numpy.

    :param x: Primer vector (np.ndarray).
    :param y: Segon vector (np.ndarray).
    :return: Escalar (float) corresponent a la distància euclidiana.
    """
    return np.linalg.norm(x - y, ord=2)


def simEuclid(x: np.ndarray, y: np.ndarray, total: int) -> float:
    """
    Retorna valor entre 0 i 1 que descriu la semblança de dos vectors.
    Similitud Euclidiana normalitzada pel factor de pel·lícules en comú.
    $$d =  \frac{1}{(1+distEuclid(U1, U2))} \times \frac{len(U1)}{n} $$

    :param x: Primer vector (np.ndarray) de valoracions en comú.
    :param y: Segon vector (np.ndarray) de valoracions en comú.
    :param total: Dimensió de l'espai total (nombre total de pel·lícules).
    :return: Escalar (float) corresponent a la semblança. Retorna 0.0 si els vectors són buits.
    """
    if len(x) == 0:
        return 0.0

    # L'enunciat utilitza 'len(U1)', que és 'len(x)' en aquest context (nombre de pelis en comú)
    similarity = (1.0 / (1.0 + distEuclid(x, y))) * (len(x) / total)

    return similarity


def simUsuaris(DataFrame: pd.DataFrame, User1: int, User2: int) -> float:
    """
    Retorna un score que representa la similitud entre User1 i User2 basada en
    la distància euclidiana sobre les puntuacions que tenen en comú.

    :param DataFrame: DataFrame pivotat (df_counts) que conté les valoracions.
    :param User1: ID (re-indexat) del primer usuari.
    :param User2: ID (re-indexat) del segon usuari.
    :return: Escalar (float) corresponent al score de similitud.
    """
    # L'enunciat utilitza la variable global 'num_movies' per a la normalització.
    # Assumint que 'num_movies' és el nombre total de pel·lícules úniques (data.nunique()['movie_id']).
    num_movies = 3706

    user1 = DataFrame.loc[User1].values
    user2 = DataFrame.loc[User2].values

    # Obtenir els índexs de les pel·lícules valorades per AMBDÓS usuaris (no NaN)
    common_rated_indices = np.isfinite(user1) & np.isfinite(user2)

    # Extreure els elements comuns
    x = user1[common_rated_indices]
    y = user2[common_rated_indices]

    return simEuclid(x, y, num_movies)

def compute_similitud(fixed_arr: np.ndarray, var_arr: np.ndarray) -> float:
    """
    Calcula la similitud euclidiana normalitzada entre els subvectors de valoracions
    que tenen en comú (no NaN). Utilitza la fórmula de simEuclid amb len(comú)/n.

    :param fixed_arr: El primer vector (np.ndarray) de valoracions.
    :param var_arr: El segon vector (np.ndarray) de valoracions.
    :return: Escalar (float) corresponent a la similitud. Retorna 0.0 si no hi ha elements en comú.
    """
    fixed_arr = np.array(fixed_arr, dtype=float)
    var_arr = np.array(var_arr, dtype=float)
    n = fixed_arr.size # La dimensió total (nombre de pel·lícules)

    # Màscara de valors comuns (sense NaN)
    mask = np.isfinite(fixed_arr) & np.isfinite(var_arr)

    x = fixed_arr[mask]
    y = var_arr[mask]

    if x.size == 0:
        return 0.0

    sim = simEuclid(x, y, n)

    return sim

def find_similar_users(DataFrame, userID, m, simfunction):
    """
    Retorna un diccionari d'usuaris similars amb les scores corresponents.

    :param DataFrame: dataframe que conté totes les dades
    :param userID: usuari respecte al qual fem la recomanació
    :param m: nombre d'usuaris que volem per fer la recomanació
    :param simfunction: mesura de similitud
    :return: dictionary amb els usuaris més similars i les seves puntuacions
    """

    # Calculate similarities with all other users
    similarities = {}
    for other_id in DataFrame.index:
        if other_id == userID:
            continue
        similarities[other_id] = simfunction(DataFrame, userID, other_id)

    # Get top m most similar users
    top_m_users = heapq.nlargest(m, similarities.items(), key=lambda x: x[1])

    # Convert to dictionary
    top_m_dict = dict(top_m_users)

    # Normalize so the sum is 1
    total = sum(top_m_dict.values())
    if total > 0:
        for user_id in top_m_dict:
            top_m_dict[user_id] /= total

    return top_m_dict

def compute_similitude_corr(fixed_arr: np.ndarray, var_arr: np.ndarray) -> float:
  """
  Calcula la similitud entre dos vectors usant el coeficient de correlació de
  Pearson sobre els subvectors formats pels elements en comú.
  El resultat es normalitza multiplicant pel factor de cobertura (num_common / len(fixed_arr)).
  No utilitza iteracions (bucles).

  :param fixed_arr: El primer vector (np.ndarray) de valoracions.
  :param var_arr: El segon vector (np.ndarray) de valoracions.
  :return: Escalar (float) corresponent a la similitud. Retorna 0.0 si no hi ha suficients elements en comú.
  """

  # Màscara de valors comuns (sense NaN)
  mask = np.isfinite(fixed_arr) & np.isfinite(var_arr)

  # Subvectors amb valoracions en comú
  sub1 = fixed_arr[mask]
  sub2 = var_arr[mask]

  num_common = len(sub1)
  # Requereix almenys 2 elements per a una correlació significativa
  if num_common < 2:
      return 0.0

  # Mitjanes
  m1 = np.mean(sub1)
  m2 = np.mean(sub2)

  # Vectors centrats
  c1 = sub1 - m1
  c2 = sub2 - m2

  # Desviacions estàndard (amb np.mean per evitar la normalització per N-1)
  s1 = np.sqrt(np.mean(c1**2))
  s2 = np.sqrt(np.mean(c2**2))

  # Casos de valoracions constants
  if s1 == 0 or s2 == 0:
      return 1.0 if np.allclose(sub1, sub2) else 0.0

  # Correlació de Pearson (covariància/producte de desviacions)
  corr = np.mean(c1 * c2) / (s1 * s2)

  # Normalització per número de pel·lícules totals
  normalized = corr * (num_common / len(fixed_arr))

  return normalized

def similarity_matrix_1(compute_distance: callable, df_counts: pd.DataFrame) -> np.ndarray:
    """
    Retorna una matriu de similitud simètrica de mida U x U (U = nombre d'usuaris).
    Cada posició (i,j) indica la similitud entre l'usuari i i l'usuari j,
    calculada iterativament usant la funció de distància proporcionada.

    :param compute_distance: Funció de similitud/distància a utilitzar (p. ex., compute_similitud).
    :param df_counts: DataFrame amb els valors que cada usuari ha donat a una peli (pivotat).
    :return: Matriu numpy de mida U x U amb les similituds.
    """
    M = df_counts.shape[0]
    matriu = np.zeros((M, M))

    for i in range(M):
        for j in range(i + 1, M):
            # Calculem la similitud només per a la meitat superior
            s = compute_distance(df_counts.iloc[i].values, df_counts.iloc[j].values)

            if np.isnan(s): s = 0.0
            matriu[i, j] = s
            matriu[j, i] = s    # Simetria

    return matriu

def similarity_matrix_2(DataFrame: pd.DataFrame) -> np.ndarray:
    """
    Retorna una matriu de similitud de mida U x U (U = nombre d'usuaris)
    utilitzant un enfocament matricial vectoritzat.

    Substitueix els NaN (ítems no avaluats) per 0 per permetre operacions matricials.
    Calcula la similitud $sim = \frac{1}{(1 + distEuclid)}$ (sense normalització per cobertura).

    :param DataFrame: DataFrame amb els valors que cada usuari ha donat a una peli (df_counts).
    :return: Matriu numpy de mida U x U amb les similituds.
    """
    # 1. Convertim el DataFrame a un array NumPy substituint NaNs per 0
    X = DataFrame.to_numpy(na_value=0).astype(float)
    M = X.shape[0] # Nombre d'usuaris

    # 2. Normes quadrades: ||x_i||^2
    x2 = np.sum(X**2, axis=1)

    # 3. Producte escalar entre totes les parelles: xy[i, j] = x_i dot x_j
    xy = np.matmul(X, X.T)

    # 4. Càlcul de la distància euclidiana al quadrat (usant la fórmula ||x_i - x_j||² = ||x_i||² + ||x_j||² - 2 * x_i dot x_j)
    x2_col = x2.reshape(-1, 1)
    d2 = x2_col + x2_col.T - 2 * xy

    # 5. Estabilitat numèrica (limitar a 0 per evitar errors de sqrt en valors -epsilon)
    d2 = np.maximum(d2, 0)

    # 6. Distància euclidiana real
    dists = np.sqrt(d2)

    # 7. Convertim distància a similitud: sim = 1 / (1 + dist)
    sim = 1.0 / (1.0 + dists)

    return sim

def find_similar_users(DataFrame: pd.DataFrame, sim_mx: np.ndarray, userID: int, m: int) -> dict[int, float]:
    """
    Troba els 'm' usuaris més similars a 'userID' utilitzant una matriu de similitud
    precalculada. Els scores de similitud es normalitzen per a que sumin 1.

    :param DataFrame: DataFrame amb els valors que cada usuari ha donat a una peli (df_counts).
    :param sim_mx: Matriu numpy de similituds (p. ex., la retornada per similarity_matrix_2).
    :param userID: ID (re-indexat) de l'usuari respecte al qual es fa la cerca.
    :param m: Nombre d'usuaris més similars a retornar.
    :return: Diccionari `{user_id: normalized_score}` amb els m usuaris més similars i les seves puntuacions normalitzades.
    """
    # Posem la diagonal a 0
    sim_mx[userID][userID] = 0

    # Seleccionem els m usuaris més similars
    top_m = np.argsort(sim_mx[userID])[-m:]

    # Extreiem els scores
    scores = np.array([sim_mx[userID][i] for i in top_m], dtype=float)

    # Normalització perquè sumin 1
    total = scores.sum()
    if total > 0:
        norm_scores = scores / total
    else:
        # Si tot és 0, repartim uniformement per evitar divisions per zero
        norm_scores = np.ones_like(scores) / len(scores)

    return {i: norm_scores[k] for k, i in enumerate(top_m)}

def weighted_average(DataFrame: pd.DataFrame, user: int, sim_mx: np.ndarray, m: int) -> dict[int, float]:
    """
    Calcula la puntuació predita de cada ítem (pel·lícula) no vist per l'usuari,
    utilitzant la mitjana ponderada de les puntuacions dels seus 'm' veïns més propers.

    La fórmula utilitzada és $\text{Pred}(u, i) = \sum_{v \in \text{Neighbors}} \text{sim}(u, v) \cdot \text{Rating}(v, i)$
    on $\text{sim}(u, v)$ ja està normalitzat per $\sum \text{sim}(u, v) = 1$.

    :param DataFrame: DataFrame pivotat (df_counts).
    :param user: ID (re-indexat) de l'usuari al qual es vol fer la predicció.
    :param sim_mx: Matriu numpy de similituds.
    :param m: Nombre d'usuaris veïns a considerar.
    :return: Diccionari `{movie_id: score_predit}` amb la puntuació predita per a les pel·lícules no vistes.
    """
    predictions = {}
    similar_users = find_similar_users(DataFrame, sim_mx, user, m)

    # Si no hi ha usuaris similars, retornar diccionari buit
    if not similar_users:
        return predictions

    # Usar Series i DataFrames per facilitar l'alineació i les operacions vectorials
    sim_weights = pd.Series(similar_users)
    neighbor_ratings = DataFrame.loc[sim_weights.index] # Valoracions dels veïns
    user_row = DataFrame.loc[user]
    unseen_mask = user_row.isna() # Màscara per a les pel·lícules no vistes per l'usuari objectiu

    # Si no hi ha pel·lícules no vistes, retornar diccionari buit
    if not unseen_mask.any():
        return predictions

    # Les valoracions candidates són les columnes (pel·lícules) on l'usuari objectiu no ha puntuat
    candidate_ratings = neighbor_ratings.loc[:, unseen_mask].to_numpy(dtype=float)
    # Pesos (similituds) en format de columna per broadcast
    weights = sim_weights.to_numpy(dtype=float)[:, None]
    # Màscara per a valors vàlids (no NaN) en les valoracions candidates (les que els veïns SÍ han puntuat)
    valid_mask = ~np.isnan(candidate_ratings)

    # Càlcul de la suma ponderada: sum(Rating * Weight)
    # np.nansum ignora els NaNs, que són les pel·lícules que el veí tampoc va puntuar
    weighted_sum = np.nansum(candidate_ratings * weights, axis=0)

    # Renormalitzar per la suma dels pesos que realment han contribuït (pel·lícules que el veí ha valorat)
    # weight_totals = sum(Weight * Valid_Mask)
    weight_totals = (valid_mask * weights).sum(axis=0)

    # Càlcul del score: weighted_sum / weight_totals
    # np.divide s'utilitza amb 'out' i 'where' per evitar warnings/errors de divisió per zero
    scores = np.divide(weighted_sum, weight_totals, out=np.zeros_like(weighted_sum), where=weight_totals > 0)

    # Construir el diccionari de prediccions
    predictions = {
        int(movie_id): float(score)
        for movie_id, score in zip(DataFrame.columns[unseen_mask], scores)
        # S'inclouen només scores predits positius (encara que en el context de MAE no és estrictament necessari, és bona pràctica)
        if score > 0
    }
    return predictions

def getRecommendationsUser(DataFrame: pd.DataFrame, user: int, sim_mx: np.ndarray, n: int, m: int) -> pd.DataFrame:
    """
    Genera una llista de les 'n' millors pel·lícules recomanades (no vistes)
    per a un usuari, basant-se en les prediccions per mitjana ponderada dels
    'm' usuaris més similars.

    :param DataFrame: DataFrame original amb totes les dades (ratings, users, movies).
    :param user: ID (re-indexat) de l'usuari al qual es fa la recomanació.
    :param sim_mx: Matriu numpy de similituds.
    :param n: Nombre de pel·lícules a recomanar.
    :param m: Nombre d'usuaris veïns a considerar.
    :return: DataFrame amb les columnes ['movie_id', 'score'] de les n millors recomanacions.
    """

    # La funció original assumeix que el DataFrame d'entrada és el global 'data',
    # així que cal construir 'df_counts' internament si no es passa com a argument.
    df_counts = build_counts_table(DataFrame)

    # Predir scores per a les pel·lícules no vistes
    movie_scores_pred = weighted_average(df_counts, user, sim_mx, m)

    # Ordenar les prediccions de major a menor score
    sorted_scores = sorted(movie_scores_pred.items(), key=lambda x: x[1], reverse=True)

    # Seleccionar les n millors
    top_n_movies = sorted_scores[:n]

    # Convertir a DataFrame de resultats
    top_n_movies_df = pd.DataFrame(top_n_movies, columns=['movie_id', 'score'])
    return top_n_movies_df

def add_testdata(traindf: pd.DataFrame, test_set: pd.DataFrame, test_in_train: float = 0.8) -> tuple[pd.DataFrame, pd.DataFrame]:
    """
    Afegeix una porció de les interaccions del 'test_set' (usuaris) al 'traindf' (interaccions)
    per garantir que hi hagi dades de valoració per a tots els usuaris en el conjunt de training.
    Per a cada usuari del 'test_set', el (1 - test_in_train)% de les seves interaccions
    es mantenen per al test final, i el 'test_in_train'% s'afegeixen al training.

    :param traindf: DataFrame que conté les dades de training inicials (majoritàriament usuaris de train).
    :param test_set: DataFrame que conté les dades d'interacció dels usuaris destinats a test (10% d'usuaris).
    :param test_in_train: Proporció de les interaccions del 'test_set' a moure a 'traindf' (per defecte 0.8).
    :return: Tupla amb dos DataFrames: (nou_train_df, nou_test_df).
    """

    final_train_list = [traindf] # Comença amb el train_set original
    final_test_list = []

    # Agrupar el test_set (10% usuaris) per usuari
    test_users_grouped = test_set.groupby('user_id')

    for user_id, user_data in test_users_grouped:
        # Calcular la porció de les mostres a mantenir per al test final (1 - test_in_train)
        n_test_samples = int(len(user_data) * (1.0 - test_in_train))

        # Assegurar mínim 1 mostra de test si l'usuari té interaccions i n_test_samples era 0
        if n_test_samples == 0 and len(user_data) > 0:
            n_test_samples = 1

        # Seleccionar aleatòriament les mostres de test (la porció a mantenir per avaluació)
        frame_test = user_data.sample(n=n_test_samples)

        # La resta (el 'test_in_train'% restant) va a train
        frame_train = user_data.drop(frame_test.index)

        # Afegir a les llistes
        final_test_list.append(frame_test)
        final_train_list.append(frame_train)

    # Concatenar tot en dos DataFrames finals
    final_train_df = pd.concat(final_train_list)
    final_test_df = pd.concat(final_test_list)

    return final_train_df, final_test_df

def evaluateRecommendations(train, test, m,n, sim):
    """
    Retorna l'error generat pel model amb MAE

    :param trein: dataframe que conté les dades de training
    :param test:  dataframe que conté les dades de testing
    :param m: nombre d'usuaris que volem per fer la recomanació
    :param n: nombre de pelis a retornar (no)
    :param sim: matriu de similitud
    :return : Escalar (float) corresponent al MAE
    """

    total_error = 0
    count = 0  # Comptador de prediccions comparades

    for user in test['user_id'].unique():
        # Corregit: passar l'usuari actual, no 'users'
        user_prediction = getRecommendationsUser(train, user, sim, n, m)

        # Merge entre prediccions i test de l'usuari
        merged = pd.merge(
            test[test['user_id'] == user][['movie_id', 'rating']],
            user_prediction[['movie_id', 'score']],
            on='movie_id'
        )

        # Suma del MAE
        total_error += (merged['rating'] - merged['score']).abs().sum()
        count += len(merged)

    # Evitar divisió per zero
    mae = total_error / count if count > 0 else 0
    return mae