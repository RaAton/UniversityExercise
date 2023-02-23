#!/bin/bash

calcola_n(){
    local n=0
    local avg=0
    local std=0

    #calcolo numero di valori nel file
    while read line || [ -n "$line" ];  #leggo il file riga per riga
    do
        if [[ -z "$line" ]]; then   #salto le righe vuote
            continue
        fi
        val=$(echo "$line" | tr -d '[:space:]')     #tolgo gli spazi
        if [[ "$val" =~ ^[+-]?[0-9]*\.?[0-9]+$ ]]; then  #controllo che sia un numero
           n=$(($n + 1))
           avg=$(($avg + $val)) 
        fi
    done < "$1"

    if [ $n -eq 0 ]         #controllo che ci sia almeno un numero
        then
        echo -e "$n\t$avg\t$std\t$doc"
        return
    fi

    avg=$(echo "scale=2; $avg / $n" | bc -l) #calcolo media

    #calcolo deviazione standard
    while read line || [ -n "$line" ];  #leggo il file riga per riga
    do
        if [[ -z "$line" ]]; then   #salto le righe vuote
            continue
        fi
        val=$(echo "$line" | tr -d '[:space:]')    #tolgo gli spazi
        if [[ "$val" =~ ^[+-]?[0-9]*\.?[0-9]+$ ]]; then
            std=$(echo "scale=2; $std + ($val - $avg)^2" | bc -l)   #calcolo la deviazione standard
        fi
    done < "$1"

    std=$(echo "scale=2; sqrt($std / $n)" | bc -l) #calcolo la radice quadrata
    echo -e "$n\t$avg\t$std\t$doc"  #stampa finale

}

visita(){
    for doc in $1/* #scorro la cartella
        do
            if [ -d $doc ]  #se è una cartella la visito
                then    
                    cd $doc
                    echo "dir : "$doc
                    visita .
                    cd ..
            elif [[ $doc = *.dat ]] #se è un file lo analizzo
                then
                calcola_n $doc
            fi
    done
}

echo "---------------------------------------------------------"
echo -e "n\tavg\tstd\tfile"
echo "dir : "$1
visita $1
echo "---------------------------------------------------------"
