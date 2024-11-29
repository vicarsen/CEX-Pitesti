
# Actualizare pe interval

Pentru a raspunde si la query-uri de forma "pe un interval $[l,r]$, modifica toate valorile $a[i]$ intr-un anume fel", va mai trebui sa facem niste modificari algoritmului de baza:
 - la fiecare modificare pe un interval $[l,r]$, aplicam modificarea pe toate nodurile in care se descompune intervalul;
 - in fiecare nod, mentinem, pe langa valoarea acestuia, o valore $lazy(node)$ ce reprezinta modificarea efectuata asupra nodului respectiv;
 - de fiecare data cand vizitam un nod, verificam daca exista modificari in acesta (prin $lazy(node)$), iar in caz afirmativ, "impingem" (propagam) modificarile la copii nodului.

Observam ca, in afara de existenta unei metode de a imbina doua intervale adiacente, acum apare si nevoia de a gasi o metoda de a aplica operatia pe interval.

Cel mai simplu pentru a intelege cum functioneaza este printr-un exemplu, asa ca vom trece direct la [exemplul 1](#exemplul-1).

# Exemple

## Exemplul 1

### Enunt

Se da un sir $A$ de $N$ numere si $Q$ query-uri de tipurile:
 1. $l$ $r$ $k$ - pe toate pozitiile $i$, cu $l \le i \le r$, adaugati $k$ la valoarea lui $A[i]$
 2. $l$ $r$ - care este suma intervalului $[l, r]$

### Solutie

Se mentine un arbore de intervale cu propagare lenesa. In $tree[node]$ mentiem suma intervalului $[l, r]$, iar in $lazy[node]$ mentinem cat am adaugat la $[l, r]$ pe fiecare pozitie.

Pentru a aduna $k$ pe in nodul $node$, avem urmatoarea modificare:
 - $tree[node] \leftarrow k \cdot (r - l + 1)$
 - $lazy[node] \leftarrow lazy[node] + k$

## Exemplul 2

### Enunt

Se da un sir $A$ de $N$ numere si $Q$ query-uri de tipurile:
 1. $l$ $r$ $k$ - pe toate pozitiile $i$, cu $l \le i \le r$, inlocuim valoarea lui $A[i]$ cu $k$
 2. $l$ $r$ - care este suma maxima a unei subsecvente incluse in $[l, r]$

### Solutie

Se mentine un arbore de intervale in care, in fiecare nod, retinem urmatoarele informatii:
 - $sum[node]$ - suma pe intreg intervalul $[l, r]$
 - $prefix[node]$ - suma maxima a unui prefix din intervalul $[l, r]$
 - $suffix[node]$ - suma maxima a unui sufix din intervalul $[l, r]$
 - $seq[node]$ - suma maxima a unei subsecvente din interval $[l, r]$

Observam ca pentru a imbina doi fii $left$ si $right$ in parintele lor, $node$, cu intervalele $[l, m]$, respectiv $[m + 1, r]$, au loc urmatoarele formule de recurenta:
 - $sum[node] \leftarrow sum[left] + sum[right]$
 - $prefix[node] \leftarrow \max(prefix[left], sum[left] + prefix[right]$
 - $suffix[node] \leftarrow \max(suffix[left] + sum[right], suffix[right])$
 - $seq[node] \leftarrow \max(seq[left], seq[right], suffix[left] + prefix[right])$

Pentru propagarea lenesa, atribuirea lui $k$ la toate elementele dintr-un nod $node$ cu intervalul $[l, r]$, transforma valorile de mai sus in:
 - $sum[node] \leftarrow k \cdot (r - l + 1)$
 - $prefix[node] \leftarrow k \cdot (r - l + 1)$ daca $k > 0$, $0$ altfel
 - $suffix[node] \leftarrow k \cdot (r - l + 1)$ daca $k > 0$, $0$ altfel
 - $seq[node] \leftarrow k \cdot (r - l + 1)$ daca $k > 0$, $0$ altfel
 - $lazy[node] \leftarrow k$

Observatie: raspunsul pentru query-urile de tip $2$ este dat doar de $seq[node]$, dar pentru calcularea acestuia ne trebuie $prefix[node]$ si $suffix[node]$, iar pentru calcularea acestora ne trebuie $sum[node]$. In multe probleme va trebui sa va ganditi ce alte valori mai trebuie tinute in noduri in afara de cea care da raspunsul insusi.

# Probleme de ONI

## [Lupusor (ONI 2022)](https://kilonova.ro/problems/137?list_id=16)

Initial, problema nu pare sa aiba legatura cu arborii de intervale, dar o putem tranforma intr-una! Pentru a face acest lucru, incepem cu urmatoarele observatii care reies destul de usor din enunt:

 1. Daca $a[i] \gt b[i]$, cartea $i$ trebuie eliminata. In caz contrar, Lupusor alege cartea $i$ de doua ori si castiga
 2. Pentru a castiga, Lupusor va alege mereu cartea cu $a[i]$ maxim si cartea cu $b[i]$ minim, pierzand cand $max(a[i]) \le min(b[i])$

### Cerinta 1

Observatia $2$ ne permite sa reformulam cerinta $1$ in termeni de intervale: daca privim fiecare carte $i$ ca pe un interval $[a[i], b[i]]$, trebuie sa gasim numarul maxim de intervale cu intersectia nevida. De asemenea, trebuie sa putem transforma un interval in altul.

Putem mentine un arbore de intervale pe multimea $[1, Amax]$, unde pe pozitia $i$ numaram cate intervale contin numarul $i$. De aici, este simplu de observat ca adaugarea unui interval $[a, b]$ este echivalenta cu a adauga $1$ pe toate pozitiile $i$, $a \le i \le b$, respectiv eliminarea unui inerval $[a, b]$ este echivalenta cu a scadea $1$ de pe toate pozitiile $i$, $a \le i \le b$. Pentru a gasi suprapunerea maxima, este suficient sa calculam maximul pe multimea $[1, Amax]$. Aceste operatii se pot face cu un arbore de intervale cu adaugari pe interval si interogari de maxim.

### Cerinta 2

Asemanator ca la [cerinta 1](#cerinta-1), vom considera fiecare carte $i$ ca pe un interval $[a[i], b[i]]$. Acum, trebuie sa numaram in cate moduri putem alege intervale astfel incat intersectia lor sa fie nevida.

Observatia cheie este urmatoarea: fixand care este intervalul cu cel mai mare $a[i]$ trebuie doar sa numaram in cate moduri putem alege carti cu $a[j] \le a[i] \le b[j]$. Altfel spus, trebuie sa numaram in cate moduri putem alege intervale ce il contin pe $a[i]$. Daca, in total, exista $k$ intervale ce il contin pe $a[i]$, atunci numarul de moduri este $2^k$, deci este suficient sa numaram cate intervale il contin pe $a[i]$.

Astfel, am redus problema la cea de la [cerinta 1](#cerinta-1): mentinand acelasi arbore de intervale ca mai devreme, raspunsul initial este $\sum_{i=1}^{n}2^{query(a[i])}$, unde prin $query(x)$ ne referim la interogare punctuala in arborele de intervale in pozitia $x$.

Totusi, modificarile sunt mai dificil de efectuat. La eliminarea unui interval $[a[i], b[i]]$, in afara de a scadea $2^{query(a[i])}$ din rezultat, trebuie sa impartim la $2$ toate valorile $2^{query(a[j])}$ pentru care $a[i] \le a[j] \le b[i]$. Asemanator, la adaugarea unui interval $[a[i], b[i]]$, in afara de a adauga $2^{query(a[i])}$ la raspuns, trebuie sa inmultim cu $2$ toate valorile $2^{query(a[j])}$ cu $a[i] \le a[j] \le b[i]$.

Aceste operatii se pot face cu un alt arbore de intervale! In acesta, vom retine pe fiecare pozitie $a[i]$ numarul de moduri de a alege intervale ce il contin pe $a[i]$. Pe restul pozitiilor lasam valoarea $0$.

La eliminarea unui interval $[a[i], b[i]]$, este suficient sa impartim la $2$ pe intervalul $[a[i], b[i]]$ si sa scadem de pe pozitia $a[i]$ valoarea $2^{query(a[i])}$. Adaugarea unui interval se face similar, inmultind in loc de a imparti si adaugand in loc de a scadea. In final, raspunsul va fi suma din arbore pe $[1, Amax]$.

Deoarece ne trebuie atat adunare, cat si inmultire, operatia generala pe actualizare pe un interval va fi de forma $a \cdot x + b$, ceea ce se poate implementa cu propagare lenesa.

## Alte probleme cu arbori de intervale

 - [Bisortare](https://kilonova.ro/problems/63) (ONI 2021)
 - [Sirbun](https://kilonova.ro/problems/556) (Baraj Seniori 2023)
 - [3dist](https://kilonova.ro/problems/141) (Baraj Seniori 2022)
 - [Perm](https://kilonova.ro/problems/2669) (Baraj Seniori 2024)

# Resurse extra

Internetul este prin de resurse educationale despre arbori de intervale si aplicatii ale acestora. Pentru pregatirea pentru baraj sau lot, recomand sa parcurgeti urmatoarele articole (si nu numai!):
 - [Efficient and easy segment trees](https://codeforces.com/blog/entry/18051) - un blog minunat de pe [Codeforces](https://codeforces.com/) ce prezinta o implementare iterativa (nerecursiva) a arborilor de intervale, atat cu cat si fara propagare lenesa. Mult mai greu de inteles, dar cod mai schematic si fara frica de a avea TLE vreodata!
 - [Li Chao Tree](https://cp-algorithms.com/geometry/convex_hull_trick.html#li-chao-tree) - o aplicatie a arborilor de intervale pentru a calcula intr-un punct valoarea maxima/minima a unui set de functii in timp logaritmic. Foarte util la optimizarea unor probleme de programare dinamica (vezi [mai sus](https://cp-algorithms.com/geometry/convex_hull_trick.html)).
 - [Stergerea dintr-o structura de date in $O(T(n) \log n)$](https://cp-algorithms.com/data_structures/deleting_in_log_n.html) - o metoda ce foloseste arborii de intervale pentru a elimina valori din orice structura de date in $O(T(n) \log n)$, daca aceasta permite adaugarea in $O(T(n))$.

