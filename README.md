# SuperSopa
Aquest projecte té com a objectiu realizar una validació experimental de l’eficiència i aplicabilitat de diferents algoritmes i estructures de dades per a cercar paraules a una sopa de lletres estrambòlica que anomenarem Super Sopa. L'enunciat sencer es pot llegir a [GRAU_A_Q1_2022_2023_projecte.pdf](/GRAU_A_Q1_2022_2023_projecte.pdf).

## Qui som?
Som [@agnesfelip](https://github.com/agnesfelip), [@JCasahuga](https://github.com/jcasahuga), [@Martaw-code](https://github.com/Martaw-code) i [@miquelt9](https://github.com/miquelt9), estudiants de la [FIB](https://www.fib.upc.edu) cursant [A](https://www.fib.upc.edu/ca/estudis/graus/grau-en-enginyeria-informatica/pla-destudis/assignatures/A).

## Què hem fet?
Hem comprovat l'eficiència i aplicabilitat del [vector ordenat](https://en.wikipedia.org/wiki/Sorted_array), la [trie](https://en.wikipedia.org/wiki/Trie), el [filtre de Bloom](https://en.wikipedia.org/wiki/Bloom_filter) i el [double hashing](https://en.wikipedia.org/wiki/Double_hashing) cercant paraules a Supersopes de diferents caracteristiques per després comparar els resultats i extreure'n conclusions. Aquestes es poden llegit a l'[informe]().

## Com executar el programa
Per executar el programa cal:
- En primer lloc cal clonar el repositori a un directori local:
```
git clone https://github.com/JCasahuga/SuperSopa.git
cd SuperSopa
```
- Seguidament és necessari compilar:
```
make -j
```
- A continuació ja podem utilitzar el fitxers .inp que es troben a [JocsDeProva](https://github.com/JCasahuga/SuperSopa/tree/main/JocsDeProva) utilitzant el següent format:
```
./program.x n < JocsDeProva/nom_fitxer.inp
```
  On _n_ és la selecció del diccionari que volem utilitzar:    
      [1] Vector ordenar    
      [2] Trie   
      [3] Filtre de Bloom   
      [4] Double Hashing   
         
## Com generar un joc de prova
Per facilitar la generació de jocs de prova es pot utilitzar el programa generador.
- De nou cal compilar si no s'ha fet previament:
```
make -j
```
- Després ja prodem generar jocs de proves utilitszant el següent format:
```
./generator.x N s < Diccionaris/nom_fitxer.txt > JocsDeProva/nom_fitxer.inp
```
  On _N_ és el nombre de caselles que el taulell tindrà per fila i columna (NxN) i _s_ serà el subconjunt de paraules que s'intentarà col·locar.


___
## Scrypts
