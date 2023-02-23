# Analisi di file .dat in una directory

Ci viene data una directory con all'interno file .dat e altre directory simili ad essa. I file contengono numeri interi o decimali, uno per riga ed eventualmente separati da righe vuote. Per ogni file .dat bisogna calcolare media aritmetica e deviazione standard.

Media Aritmetica: $\mu = \frac{1}{N} \sum\limits_{i=1}^{N} x_i$

Deviazione Standard: $\sigma = \sqrt{\frac{1}{N} \sum\limits_{i=1}^{N} (x_i - \mu)^2}$

dove:

- X è l'insieme dei numeri
- n è la cardinalità dell'insieme X

Vogliamo tabulare l'output secondo il seguente schema:

| n     | avg      | std      | file       |
|-------|----------|----------|------------|
| #file | μ        | σ        | nomefile   |

Le righe invece sono strutturate con il nome della directory e subito sotto tutti i file che sono al suo interno.
