CC := g++ -ansi -pedantic -Wall -std=c++11
LISTE := Liste/
TRAJET := Trajet/
CATALOGUE := Catalogue/
OBJ := obj/


trajet :  $(OBJ)Liste.o $(OBJ)Maillon.o $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o
	$(CC)  $(OBJ)Liste.o $(OBJ)Maillon.o $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o -o trajet

$(OBJ)Liste.o : $(LISTE)Liste.cpp
	$(CC) -c $(LISTE)Liste.cpp -o $(OBJ)Liste.o

$(OBJ)Maillon.o : $(LISTE)Maillon.cpp
	$(CC) -c $(LISTE)Maillon.cpp -o $(OBJ)Maillon.o

$(OBJ)Catalogue.o : $(CATALOGUE)Catalogue.cpp
	$(CC) -c $(CATALOGUE)Catalogue.cpp -o $(OBJ)Catalogue.o

$(OBJ)Trajet.o : $(TRAJET)Trajet.cpp
	$(CC) -c $(TRAJET)Trajet.cpp -o $(OBJ)Trajet.o

$(OBJ)TrajetSimple.o : $(TRAJET)TrajetSimple.cpp
	$(CC) -c $(TRAJET)TrajetSimple.cpp -o $(OBJ)TrajetSimple.o

$(OBJ)TrajetCompose.o : $(TRAJET)TrajetCompose.cpp
	$(CC) -c $(TRAJET)TrajetCompose.cpp -o $(OBJ)TrajetCompose.o

clean :
	rm -f $(OBJ)*.o
	rm -f trajet
