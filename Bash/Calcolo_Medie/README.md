# Analisi di file .dat in una directory

Ci viene data una directory con all'interno file .dat e altre directory simili ad essa. I file contengono numeri interi o decimali, uno per riga ed eventualmente separati da righe vuote. Per ogni file .dat bisogna calcolare media aritmetica e deviazione standard.

Media Aritmetica: μ = Σ(xi)/N

Deviazione Standard: σ = √(Σ(xi – μ)² / N)

dove:
- X è l'insieme dei numeri	
- N è la cardinalità dell'insieme X

Vogliamo tabulare l'output secondo il seguente schema:

| n     | avg      | std      | file       |
|-------|----------|----------|------------|
| #file | μ        | σ        | nomefile   |

Le righe invece hanno prima dir: "nomedir" contenuto dir dir2: ...

