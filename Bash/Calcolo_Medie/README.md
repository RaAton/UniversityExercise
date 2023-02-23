#Calcolo_Medie
Ci viene data una directory con all'interno file .dat e altre directory simili ad essa
I file contengono numeri interi o decimali, uno per riga ed eventualmente separati da righe vuote.
Per ogni file .dat bisogna calcolare media aritmetica e deviazione standard

Media Aritmetica: μ = Σ(xi)/N

Deviazione Standard: σ = √(Σ(xi – μ)² / N)

dove:

- X è l'insieme dei numeri
- N è la cardinalità dell'insieme X

e vogliamo tabulare l'output secondo il seguente schema:

------------------------------------------------------
n  avg  std  file

(= #file) (= μ)  (= σ)  (= nomefile)
------------------------------------------------------

le righe invece hanno prima
dir: "nomedir"
contenuto dir
dir2: ...

il file viene ordinato in maniera crescente sul campo n mantenendo comunque le divisioni tra cartelle. (non si può usare "sed" e "awk")

Fare lo stesso in C usando le chiamate di sistema per i file.

Consegnare un file in formato “.tar.gz”o “.zip” contenente:
 -Lo script Bash
 -Il codice sorgente del programma C (e gli eventuali include files.h)
 -Un Makefile per compilare il programma C e per eseguire i test
 -Una o più directory contenentii file “.dat” per eseguire i test e dimostrare la funzionalità dello script e del programma C. Limitare la dimensione di tali directory a non più di 2MB e massimo 200 file.

Il comando makese lanciato senza argomenti, deve compilare il programma C.
Il Makefiledeve avere almeno i seguenti target fittizi(PHONY): test1e test2. Il primo target (test1) manda in esecuzione lo script Bashsuuna delle directory di testfornite.Il secondo target fittizio (test2) manda in esecuzione il programma Csu una delle directory di testfornite.
