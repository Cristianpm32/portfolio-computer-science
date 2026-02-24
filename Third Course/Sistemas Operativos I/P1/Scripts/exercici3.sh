#!/bin/bash

# Comprova si el nombre d'arguments no és igual a 1
if [[ $# -ne 1 ]]; then
    echo "Es requereix el següent format ./exercici3.sh <número>"

# Comprova si l'argument no és un nombre
elif ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "El paràmetre ha de ser un numero"

# Si l'argument és un nombre vàlid, imprimeix la taula de multiplicar
else
    for ((i=1; i<=10; i++)); do
        echo "$1 x $i = $(($1*$i))"
    done
fi
