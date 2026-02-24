#!/bin/bash

# Comprova si el nombre d'arguments no és igual a 1
if [ $# -ne 1 ]; then
	echo "El nombre de paràmetres és incorrecte. El format ha de ser ./exercici4.sh <cadena>"

# Comprova si la cadena que es rep sigui un número
elif [[ $1 =~ ^[0-9]+$ ]]; then
	echo "La cadena és un numero"


# Comprova si el format de la cadena és correcte
elif ! [[ $1 =~ ^[a-zA-Z]+$ ]]; then
	echo "El format de la cadena no és correcte"

else

	echo "Longitud de la cadena: ${#1}"
	echo "Cadena en majúscules ${1^^}"

fi