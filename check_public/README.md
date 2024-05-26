# PA - Tema 2: Politisti, Programatori si Scandal

## Descriere implementare

### Problema 1: Numarare

-   Dupa ce citesc listele de adiacenta pentru cele 2 grafuri, construiesc listele de
    adiancenta pentru un alt graf, ce contine doar muchiile comune primelor doua.
-   Apelez functia uint64_t get_nr_total_paths() pentru a gasi numarul de lanturi
    elementare de la nodul 1 la nodul N, folosind programare dinamica.
    dp[node] retine numarul de lanturi catre nodul node.
-   Deoarece graful este un DAG si este deja sortat topologic (u < v, pentru oricare muchie (u,v)), nu trebuie sa folosesc un vector pentru a retine ce noduri au fost deja vizitate. Pentru fiecare vecin j al unui nod i, extind numarul de lanturi care ajung in j cu numarul de lanturi care au ajuns in i. Asta inseamna ca dp[v] = sum(dp[u]),
    pentru toate nodurile u care au o muchie catre v. La final voi returnez dp[N].

### Complexitate temporala

    T(N,M) = O(N + M) (calculul intersectiei) + O(N + M') (gasirea numarului de lanturi) =
    O(N + M)
    N - numarul de noduri
    M - numarul de muchii
    M' - numarul de muchii din graful cu muchii comune

    M' < M

---

### Problema 2: Trenuri

-   Am retinut listele de adiacenta pentru orase sub forma unui unordered_map.
-   get_longest_path_length:
    Algoritmul este un DFS modificat pentru a gasi cele mai lungi drumuri de la nodul sursa la celelalte. Mai intai cream vectorii visited si dist. distanta initiala catre fiecare nod este INT_MIN. Apelam topo_sort pentru fiecare nod nevizitat pentru
    a adauga toate nodurile din graf in stiva astfel incat atunci cand scoatem un nod din stiva, toate nodurile care au muchii ce intra in el au fost deja procesate. In continuare scoatem cate un nod din stiva si verificam daca distantele catre vecinii sai pot fi marite. La final returnez distanta catre nodul destinatie

### Complexitate temporala

    T(N,M) = O(N + M) (get_longest_path_length)
    N - numarul de noduri
    M - numarul de muchii

---

### Problema 3: Drumuri obligatorii

-   Pentru a rezolva problema trebuie sa gasim min(dist(x,node) + dist(y, node) + dist(node, z)), node fiind un nod intermediar, node = 1..N
-   Deoarece graful este ponderat, apelez algoritmul lui Djikstra clasic de 3 ori, cu x, y si z ca surse. Pentru al treilea apel folosesc graful transpus (cu orientarile muchiilor inversate). In acest moment am obtinut 3 vectori de distante: dist_from_x, dist_from_y si
    dist_to_z.
-   Voi alege fiecare nod intermediar, astfel incat suma lungimii drumului de la x la nod, de la y la nod si de la nod la z sa fie minima.

### Complexitate temporala

    T(N,M) = 3 * O(M * log(N)) (djikstra) + O(N) (gasirea submultimii de muchii de cost minim) = O(M * log(N))
    N - numarul de noduri
    M - numarul de muchii
