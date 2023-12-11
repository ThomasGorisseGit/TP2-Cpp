CC := g++ -ansi -pedantic -Wall -std=c++11 
LISTE := Liste/
TRAJET := Trajet/
CATALOGUE := Catalogue/
OBJ := obj/
SRC := Src/
EXE := trajets


# Si on veut utiliser la trace : 'make trace=1'
ifdef trace
    CC += -DMAP
endif

$(EXE) :  $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o $(OBJ)main.o
	$(CC) $(OBJ)Catalogue.o $(OBJ)Trajet.o $(OBJ)TrajetSimple.o $(OBJ)TrajetCompose.o $(OBJ)main.o -o $(EXE)

$(OBJ)Catalogue.o : $(SRC)$(CATALOGUE)Catalogue.cpp $(SRC)$(CATALOGUE)Catalogue.h 
	$(CC) -c $(SRC)$(CATALOGUE)Catalogue.cpp -o $(OBJ)Catalogue.o 

$(OBJ)Trajet.o : $(SRC)$(TRAJET)Trajet.cpp $(SRC)$(TRAJET)Trajet.h
	$(CC) -c $(SRC)$(TRAJET)Trajet.cpp -o $(OBJ)Trajet.o

$(OBJ)TrajetSimple.o : $(SRC)$(TRAJET)TrajetSimple.cpp $(SRC)$(TRAJET)TrajetSimple.h
	$(CC) -c $(SRC)$(TRAJET)TrajetSimple.cpp -o $(OBJ)TrajetSimple.o

$(OBJ)TrajetCompose.o : $(SRC)$(TRAJET)TrajetCompose.cpp $(SRC)$(TRAJET)TrajetCompose.h
	$(CC) -c $(SRC)$(TRAJET)TrajetCompose.cpp -o $(OBJ)TrajetCompose.o

$(OBJ)main.o : main.cpp
	$(CC) -c main.cpp -o $(OBJ)main.o

clean :
	rm -f $(OBJ)*.o
	rm -f $(EXE)