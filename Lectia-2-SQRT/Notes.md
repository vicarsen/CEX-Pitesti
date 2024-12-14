# [Descompunere in radicali](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)

Am discutat acum 2 saptamani despre arbori de intervale. La unele probleme, nu putem folosi arbori de intervale sau solutia cu arbori de intervale e greu de gasit. Urmatorul cel mai bun lucru este descompunerea in radicali care functioneaza in felul urmator:
 - se imparte tot sirul in "bucket"-uri de lungime fixa $S$ (de obicei $\sqrt n$);
 - se calculeaza raspunsul pentru fiecare bucket;
 - o interogare pe un interval [l, r] se descompune in bucket-urile incluse complet in interval (in numar de maxim $\frac{r-l}{S}$) si doua "bucati" de bucket-uri procesate element cu element (in medie, $S$ elemente);
 - o actualizare, actualizeaza atat elementul respectiv, cat si bucket-ul ce il contine.

Acum, din punct de vedere al complexitatii de timp, fiecare interogare e compusa din maximum $\frac{r-l}{S}+S$ pasi, iar fiecare actualizare maximum $S$ pasi.

Considerand cel mai rau caz, si anume cand $l=1$ si $r=n$, obtinem un numar maxim de $\frac{N}{S}+S$ pasi pentru o interogare. Acum trebuie sa ne gandim care este valoarea lui $S$ pentru care aceasta expresie are valoare minima. Pentru acest lucru, putem apela la derivate: daca derivam expresia in functie de $S$ si egalam cu $0$ pentru a gasi punctele critice, obtinem: $\frac{-N}{S^2}+1=0 \iff S=\sqrt N$, iar numarul de pasi efectuati este $\frac{N}{\sqrt N} + \sqrt N = 2\sqrt N$, deci in total vom avea complexitatea $O(Q\sqrt N)$.

Totusi, observam ca am facut 2 presupuneri despre interogari:
 - procesarea unui bucket intreg are complexitatea $O(1)$;
 - procesarea unui element din capete are complexitatea $O(1)$.

In unele cazuri, aceste lucruri nu vor fi adevarate. Putem avea $O(f(n))$ pentru un bucket si $O(g(n))$ pentru un element. In cazul asta, $S=\sqrt N$ poate fi o alegere buna, dar nu este neaparat optim! Puteti repeta pasii de mai sus, si anume de a deriva expresia $f(n) \cdot \frac{N}{S} + g(n) \cdot S$ in functie de $S$ pentru a gasi punctele critice si valoarea lui $S$ pentru care expresia este minima.

Alte probleme pur si simplu sunt menite sa fie rezolvate altfel. Totusi, asta nu inseamna ca solutia cu descompunere in radicali nu poate lua 100p. O posibila metoda prin care autorii testelor au facut ca solutiile cu descompunere in radicali sa nu se incadreze in limita de timp este prin a face niste teste adversariale impotriva unor valori de marime a blocurilor. O metoda de a trece astfel de teste, este de a modifica putin marimea unui bucket.

## Exemple

 - Query-uri de maxim si update-uri de inlocuire
 - [Holes](https://codeforces.com/contest/13/problem/E) - Codeforces

## Articole

 - [CPAlgo](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)
 - [RoAlgo](https://edu.roalgo.ro/dificil/square-root-decomposition/)

# Amanarea actualizarilor

La unele probleme, poate fi util sa amanam diverse actualizari si sa le executam astfel:
 - la fiecare interogare, trecem prin toate cele amanate pana aici si le aplicam pe raspunsul interogarii;
 - la a $\sqrt q$-a interogare, aplicam actualizarile si reconstruim structura folosita.

Ca si la descompunerea in radicali, fix $\sqrt q$ nu e mereu optim, asa ca si aici putem aplica optimizarea de mai sus.

Observatie: de cele mai multe ori, exista si o solutie mai optima, dar aceasta poate fi mult mai complicata! In conditii de concurs, orice solutie (corecta) ce se incadreaza in limitele de timp si memorie e buna, deci nu are sens sa va complicati daca gasiti o solutie scurta care functioneaza.

## Exemple

 1. Se da un sir de $n$ numere naturale si $q$ query-uri: 1 l r - sa se calculeze suma numerelor din sir cu indicii din intervalul [l, r]; 2 l r x - se aduna x la fiecare numar cu indice din intervalul [l, r].

# [Algoritmul lui Mo](https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm)

Algoritmul lui Mo este o metoda de a raspunde (offline) la query-uri, cu complexitate de timp $O((N+Q)\sqrt N)$. Pasii acestuia sunt:
 - se sorteaza toate query-urile $[l, r]$ crescator dupa $\lfloor \frac{l}{\sqrt N} \rfloor$, iar in caz de egalitate, descrescator dupa $r$;
 - se parcurg query-urile in aceasta ordine si de fiecare data se adauga elementele lipsa din intervalul curent / se elimina elementele extra din intervalul curent pana cand se ajunge la intervalul query-ului.

Complexitatea este de $O((N+Q)\sqrt N)$, deoarece:
 - la fiecare query, datorita sortarii, capatul stanga se muta cu maxim $\sqrt N$ pozitii, deci in total maximum $Q\sqrt N$ mutari;
 - pentru fiecare valoare posibila a lui $\lfloor \frac{l}{\sqrt N} \rfloor$, capatul dreapta parcurge maxim $N$ elemente. Deci, in total, maximum $N\sqrt N$ mutari;
 - in total, maxim $(N+Q)\sqrt N$ mutari.

Observatie: o alegere mai buna pentru marimea bucket-urilor este $S=$, deoarece trebuie minimizata expresia $QS+\frac{N^2}{S}$, avand valoare minima pentru $Q - \frac{N^2}{S^2}=0 \iff S=\frac{N}{\sqrt Q}$, caz in care complexitatea este $O(N \sqrt Q)$. In practica, aceasta abordare este avantajoasa in special atunci cand avem mult mai multe query-uri decat elemente in vector.

Observatie 2: complexitatile de mai sus depind de faptul ca adaugarea/eliminarea unui element se face in $O(1)$. Daca aceasta se face, in schimb, in $O(f(n))$, complexitatea finala va fi $O((N+Q)\sqrt N f(n))$, respectiv $O(N \sqrt Q f(n))$, in functie de marimea aleasa pentru bucket. Nu mai are sens sa derivam expresia de mai sus luand in calcul si pe $f(n)$, deoarece toate operatiile sunt de acelasi tip (adaugare/eliminare).

Intrebari:
 - algoritmul lui Mo pastreaza sau nu amortizarea operatiei de adaugare/eliminare?

## Exemple

 - [DQUERY](https://www.spoj.com/problems/DQUERY/) - Spoj

## Articole

 - [CPAlgo](https://cp-algorithms.com/data_structures/sqrt_decomposition.html#mos-algorithm)
 - [RoAlgo](https://edu.roalgo.ro/dificil/square-root-decomposition/#impartirea-queryurilor-in-bucati-de-radical-algoritmul-lui-mo)
 - [Codeforces](https://codeforces.com/blog/entry/81716)

# Extra

 - [Algoritmul lui Mo pe arbori](https://codeforces.com/blog/entry/43230) - o metoda de a aplica algoritmul lui Mo asupra unor query-uri pe arbori (mai exact, pe lantul dintre doua noduri date, u si v)
 - [An alternative sorting order for Mo's algorithm](https://codeforces.com/blog/entry/61203) (+ comentariul lui [GreenGrape](https://codeforces.com/blog/entry/61203?#comment-451304)) - un blog de pe Codeforces despre o metoda de sortare pentru algoritmul lui Mo bazata pe curbe Hilbert, ce reduce complexitatea de la $O((n+q)\sqrt n)$ la $O(n \sqrt q)$

# Tema

Implementati una dintre urmatoarele probleme:

 - Descompunere in radicali: [XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E) - Codeforces
 - Descompunere in radicali: [kth](https://kilonova.ro/problems/542) - ONI, clasa a VIII-a, 2023
 - Algoritmul lui Mo: [fsecv](https://kilonova.ro/problems/1814) - Lot Juniori 2019
 - Algoritmul lui Mo: [Infinity War](https://kilonova.ro/problems/1837) - RMI 2015

