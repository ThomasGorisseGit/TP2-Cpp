CC := g++ -ansi -pedantic -Wall -std=c++11 -DMAP -g
LISTE := Liste/
TRAJET := Trajet/
CATALOGUE := Catalogue/
OBJ := obj/
EXE := exe


$(EXE) :  $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o $(OBJ)main.o
	$(CC) $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o $(OBJ)main.o -o $(EXE)



$(OBJ)Catalogue.o : $(CATALOGUE)Catalogue.cpp $(CATALOGUE)Catalogue.h 
	$(CC) -c $(CATALOGUE)Catalogue.cpp -o $(OBJ)Catalogue.o 

$(OBJ)Trajet.o : $(TRAJET)Trajet.cpp $(TRAJET)Trajet.h
	$(CC) -c $(TRAJET)Trajet.cpp -o $(OBJ)Trajet.o

$(OBJ)TrajetSimple.o : $(TRAJET)TrajetSimple.cpp $(TRAJET)TrajetSimple.h
	$(CC) -c $(TRAJET)TrajetSimple.cpp -o $(OBJ)TrajetSimple.o

$(OBJ)TrajetCompose.o : $(TRAJET)TrajetCompose.cpp $(TRAJET)TrajetCompose.h
	$(CC) -c $(TRAJET)TrajetCompose.cpp -o $(OBJ)TrajetCompose.o

$(OBJ)main.o : main.cpp
	$(CC) -c main.cpp -o $(OBJ)main.o

clean :
	rm -f $(OBJ)*.o
	rm -f trajet
