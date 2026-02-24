#!/bin/bash

# Comprova si el nombre d'arguments és igual a 2
if [ $# -ne 2 ]; then
    echo "Es requereix el següent format: ./exercici2.sh <fitxer> <permisos_octals>"
    exit 1

# Comprova si el fitxer no existeix
elif ! [ -f "$1" ]; then
    echo "El fitxer no existeix"
    exit 1

# Comprova si el fitxer està buit
elif ! [ -s "$1" ]; then
    echo "El fitxer està buit. Desitja continuar?"
    exit 1

# Comprova si el segon argument té el format correcte d'octals. 
elif ! [[ "$2" =~ ^[0-7]{3}$ ]];then 
    echo "El format de $2 no és correcte. Recorda que han de ser 3 dígits en octal"
    exit 1

else

    echo "Permisos actuals de $1 $(ls -l "$1" | awk '{ print $1 }')"
    chmod "$2" "$1"
    echo "Nous permisos de $1 $(ls -l "$1" | awk '{ print $1 }')"
fi
exit 0

