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
