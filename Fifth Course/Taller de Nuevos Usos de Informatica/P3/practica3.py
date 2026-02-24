import re
import numpy as np
from itertools import combinations

def get_open_ngrams(word: str, n: int, include_boundaries: bool = True) -> set:
    """Genera un conjunt d’n-grams oberts per a una paraula donada, amb un tractament específic dels límits.

    Args:
        word (str): La paraula d’entrada.
        n (int): L’ordre de l’n-gram (per exemple, 2 per a bigrames, 3 per a trigrames).
        include_boundaries (bool): Si és True, afegeix un guió baix '_' al principi i al
                                final de la paraula per incloure els límits inicial/final,
                                però només combina el caràcter de límit amb el primer/últim
                                caràcter real de la paraula.

    Returns:
        set: Un conjunt d’n-grams oberts únics.
    """
    open_ngrams = [ ''.join(o) for o in combinations(word, n)]

    if include_boundaries:
      open_ngrams.append("_" + word[:n-1])
      open_ngrams.append(word[-n+1:] + "_")


    return set(open_ngrams)

def X_ngrams(list_of_texts):

  X_ngrams = []
  for text in list_of_texts:

    text_lower = text.lower()
    words_in_text = re.findall(r'\b\w+\b', text_lower)

    # 1. Creem un conjunt temporal per fer la UNIÓ de tots els bigrames d'aquest text
    current_text_bigrams = set()

    for word in words_in_text:
        # Obtenim els bigrames de la paraula (suposant que retorna un set o llista)
        bigrams = get_open_ngrams(word, 2, include_boundaries=True)

        # 2. Fem l'update per unir-los al conjunt del text (evita duplicats)
        current_text_bigrams.update(bigrams)

    # 3. Convertim el conjunt final a llista i l'afegim a la llista principal (X_train_ngrams)
    X_ngrams.append(list(current_text_bigrams))

  return X_ngrams

def MultinomialNBfit(X, y):
        """
        Aquesta funció és la responsable d' "aprendre" del conjunt d'entrenament,

        Args:
            X (sparse matrix): Matriu de característiques (e.g., TF-IDF) d'entrenament.
            y (array-like): Etiquetes de classe per a cada mostra.
        """

        # El primer que fem és obtenir les classes úniques que tenim a la mostra
        classes_uniques = np.unique(np.array(y))
        # La quantitat de features/paraules/bigrames que tenim a la mostra
        V = X.shape[1]


        # L'objectiu en aquesta funció és calcular les probabilitats P(w_i | c),
        # és a dir, les probabilitats d'obtenir un bigrama si estem en una llengua concreta
        # Per a fer-ho, utilitzem el model multinomial amb suavitzat de Laplace per evitar 0

        # Relacionem les paraules i les classes mitjançant aquest diccionari
        # Aquí acumularem els TF_IDF de cada paraula en cada classe
        score_paraula_classe = {classe:np.zeros(V) for classe in classes_uniques} # Aquí volem calcular Ni_c = Sum d in C(TF_IDF(wi, d))

        # En aquest punt sumem (en paralel) per cada document (text), el TF_IDF de cada paraula (bigrama) i ho associem a la classe (llengua) corresponent
        for i, document in enumerate(X):
          classe = y[i]

          # Aquí hem de filtrar com si fos una màscara pels index del document, ja que estem utilitzant Compressed Row Sparse
          # Estem sumant en paralel els valors no nuls de document.data
          score_paraula_classe[classe][document.indices] += document.data

        # Treballem amb probabilitats logarítmiques per evitar underflow
        # (producte de probabilitats acostumen a ser valors molt propers a 0)
        # Com que el logaritme és una funció injectiva i creixent, a l'hora de determinar
        # el màxim dels valors, ens farà el mateix servei.

        log_probs = {}
        for classe in classes_uniques:
          # Aquí sumem els scores de cada bigrama en la llengua. Amb això mesurem quants bigrames té cada llengua.
          total = np.sum(score_paraula_classe[classe])
          # Finalment, apliquem el suavitzat de laplace, i calculem (una magnitud proporcional a)
          # la probabilitat d'obtenir un bigrama si estem a la classe c.
          log_probs[classe] = np.log((score_paraula_classe[classe] + 1) / (total + V))

        model = {
            'classes': classes_uniques,
            'log_probs': log_probs
        }

        return model

def MultinomialNBpredict(model, X, y):
        """
        Aplica el classificador Naive Bayes.

        Args:
            model (dict): El model entrenat retornat per MultinomialNBfit.
            X (sparse matrix): Matriu de característiques (e.g., TF-IDF) de test.
            y (array-like): Etiquetes de classe per a cada mostra del test (per calcular accuracy).
        """


        classes = model['classes']
        log_probs_dict = model['log_probs']

        # Tenim:
        # X (Matriu de Documents):
        #    Files = Documents
        #    Columnes = Paraules (Bigrames)
        # Cada cel·la (i, j) conté el TF_IDF del Document 'i' i Paraula 'j'
        #
        # log_probs_dict (Probabilitats per Classe):
        #    Podem imaginar-ho com una matriu on:
        #    Files = Classes (Cat, Eng, Spa...)
        #    Columnes = Paraules
        # Cada cel·la (i, j) conté el logaritme de la probabilitat que la Paraula 'j' sigui de la Classe 'i'
        #
        # L'OBJECTIU FINAL:
        # Crear una matriu de PREDICCIONS (Scores) on:
        # Files = Documents
        # Columnes = Classes
        # Cada cel·la (i, j) conté la probabilitat que el Document 'i' sigui de la Classe 'j'.

        #  for classe in class
        #     for bigrama in bigrames
        #       for
        #          sumes



        # PAS 1: Convertir el diccionari de log_probs_dict a una MATRIU (n_classes x n_features)
        # Necessitem alinear les probabilitats en l'ordre correcte de les 'classes'
        # Stackeja els arrays horitzontals un sobre l'altre
        matriu_log_probs = np.vstack([log_probs_dict[c] for c in classes])

        # PAS 2: Càlcul vectorial de les prediccions (El "core" de l'optimització)
        # X té dimensions (n_docs, n_features)
        # matriu_log_probs.T té dimensions (n_features, n_classes)
        # El resultat serà una matriu (n_docs, n_classes) amb els scores acumulats

        # Amb aquesta multiplicació matricial, ens estalviem haver de fer els 2 bucles aniuats i el producte escalar
        matriu_scores = X @ matriu_log_probs.T # La cel·la (i, j) et dona el log de la probabilitat que el document i estigui en la classe j

        # PAS 3: Triar la millor classe per a cada document
        # Busquem l'índex de la columna amb el valor màxim per a cada fila (axis=1)
        indexs_millor_classe = np.argmax(matriu_scores, axis=1) # Per cada document, et dona la millor class

        # Mapegem els índexs (0, 1, 2...) a les etiquetes reals (ex: 'cat', 'eng', 'spa')
        y_predicted = classes[indexs_millor_classe]

        # PAS 4: Calcular l'accuracy
        # Comparem tot el vector de prediccions amb el vector real de cop
        if len(y) > 0:
            correct_predictions = np.sum(y_predicted == y)
            accuracy = correct_predictions / len(y)
        else:
            accuracy = 0.0
        return accuracy