#!/bin/bash

# Comprova si el nombre d'arguments és igual a 2
if [ $# -ne 2 ]
then
    echo "Es requereix el següent format: ./ejercicio1.sh <fitxer1> <fitxer2>"
    exit 1

# Comprova si almenys un dels fitxers no existeix
elif [ ! -f "$1" -o ! -f "$2" ]
then
    echo "Almenys un dels fitxers no existeix."
    exit 1

# Comprova si per almenys un dels dos fitxers no es tenen permisos de lectura
elif [ ! -r "$1" -o ! -r "$2" ]
then
    echo "No tens permisos de lectura per a un dels fitxers."
    exit 1

# Comprova si almenys un dels fitxers està buit
elif [ ! -s "$1" -o ! -s "$2" ]
then
    echo "Almenys un dels fitxers està buit."
    exit 1
else
    echo "Mida del fitxer $1 : "; ls -l "$1" | awk '{ print $5 }'
    echo "Mida del fitxer $2 : "; ls -l "$2" | awk '{ print $5 }'
	cat "$1" "$2" >> concatenats.txt
    echo "Mida del fitxer concatenat : "; ls -l concatenats.txt | awk '{ print $5 }'
fi

exit 0


