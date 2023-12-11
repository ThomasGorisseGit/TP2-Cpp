# Test trajet simple

Création d'un trajet simple classique

```
2
1
A
B
Bus
1
```

==> Trajet créé

Creation d'un trajet Arrivée = Départ

```
2
1
A
A
```

==> Erreur car deux fois le même nom

```
2
1
A
A
B
Bus
1
```

==> Pas erreur car arrivé remplacé par B

# Test recherche simple

Recherche trajet inexistant

```
2
1
A
B
Bus
3
A
C
```

==> pas de trajet trouvé

Recherche trajet existant

```
2
1
A
B
Bus
3
A
B
```

==> trajet trouvé

Recherche un trajet composé

```
2
2
A
C
B
Bus
C
Camion
3
A
C
```

==> trajet trouvé A->C

Recherche dans un trajet composé

```
2
2
A
C
B
Bus
C
Camion
3
A
B
```

==> trajet trouvé A->B (trajet n°1 du trajet composé)

Recherche simple d'un trajet composé avec un seul trajet

```
2
2
A
B
B
Bus
3
A
B
```

==> 2 trajets trouvés (un simple et un composé (le global))

# Test recherche avancée

Recherche d'un trajet composé avec un seul composé

```
2
2
A
C
B
Bus
C
Camion
3
A
C
```

==> trajet trouvé A->C ( A->B en bus puis B->C en camion)

Recherche d'un trajet composé avec un simple

```
2
1
A
B
Bus
3
A
B
```

==> trajet trouvé A->B

Recherche d'un trajet composé avec un trajet simple et un composé

```

2
1
A
B
Bus
2
2
A
C
B
Bus
C
Camion
3
A
C

```

==> trajet trouvé A->C ( A->B en bus puis B->C en camion)
Test du sujet de TP

```
2
1
A
B
MT1
2
2
B
C
Y
MT3
C
MT2
2
1
B
C
MT1
2
2
A
C
Z
MT2
C
MT1
3
A
C
1
4
A
C
5
```

==> 3 trajets trouvés (A->B, B->Y, Y->C et A->B, B->C et A->Z, Z->C)
