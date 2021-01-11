
# Fichier exécutable produit
EXEC=typerabais
EXECTEST=testrabais


# Répertoire contenant les fichiers source
SOURCE=src

# Répertoire contenant les fichiers compilés
BINAIRE=bin
TESTS=test


# Répertoire contenant les données utilisées par le logiciel
DONNEES=data

# Nom du fichier contenant les données
CLIENTS=clients.dat

# =======================
# Compilation du logiciel
# =======================

# commande par défaut, construit un exécutable appelé $(EXEC) et le lance.
# l'exécutable est appelé avec ./$(EXEC) nomfichierdonnees.dat
all: $(BINAIRE)/$(EXEC)
	./$(BINAIRE)/$(EXEC) $(DONNEES)/$(CLIENTS)

# Fait le "linking" entre les fichiers objets pour produire l'exécutable
$(BINAIRE)/$(EXEC): $(BINAIRE)/main.o $(BINAIRE)/client.o $(BINAIRE)/rabais.o $(BINAIRE)/facture.o $(BINAIRE)/afficheur.o
	g++ -o $@ $^ 

# Compile le "main" pour produire le fichier objet.
$(BINAIRE)/main.o: $(SOURCE)/main.cpp $(SOURCE)/rabais.h $(SOURCE)/facture.h
	mkdir -p $(BINAIRE)
	g++ -o $@ -c $<

# Compile la classe Client pour produire le fichier objet.
$(BINAIRE)/client.o: $(SOURCE)/client.cpp $(SOURCE)/client.h
	g++ -o $@ -c $<

# Compile la classe Rabais pour produire le fichier objet.
$(BINAIRE)/rabais.o: $(SOURCE)/rabais.cpp $(SOURCE)/rabais.h $(SOURCE)/client.h $(SOURCE)/facture.h
	g++ -o $@ -c $<

# Compile la classe Facture pour produire le fichier objet.
$(BINAIRE)/facture.o: $(SOURCE)/facture.cpp $(SOURCE)/facture.h
	g++ -o $@ -c $<

# Conmpile la classe Afficheur pour produire le fichier objet.
$(BINAIRE)/afficheur.o: $(SOURCE)/afficheur.cpp $(SOURCE)/afficheur.h $(SOURCE)/rabais.h $(SOURCE)/facture.h
	g++ -o $@ -c $<

# ===========
# Utilitaires
# ===========

# ___________________Tests_______________________

test: $(TESTS)/$(BINAIRE)/$(EXECTEST)
	./$(TESTS)/$(BINAIRE)/$(EXECTEST)

$(TESTS)/$(BINAIRE)/$(EXECTEST): $(TESTS)/$(BINAIRE)/main.o $(TESTS)/$(BINAIRE)/test.o $(TESTS)/$(BINAIRE)/rabais.o $(TESTS)/$(BINAIRE)/facture.o $(TESTS)/$(BINAIRE)/client.o
	g++ -o $@ $^ -lcppunit

$(TESTS)/$(BINAIRE)/main.o: $(TESTS)/$(SOURCE)/main.cpp $(TESTS)/$(SOURCE)/test.h
	mkdir -p $(TESTS)/$(BINAIRE)
	g++ -o $@ -c $<

$(TESTS)/$(BINAIRE)/test.o: $(TESTS)/$(SOURCE)/test.cpp $(TESTS)/$(SOURCE)/test.h $(SOURCE)/rabais.h
	g++ -o $@ -c $<

$(TESTS)/$(BINAIRE)/rabais.o: $(SOURCE)/rabais.cpp $(SOURCE)/rabais.h $(SOURCE)/facture.h $(SOURCE)/client.h
	g++ -o $@ -c $<

$(TESTS)/$(BINAIRE)/facture.o: $(SOURCE)/facture.cpp $(SOURCE)/facture.h
	g++ -o $@ -c $<
	
$(TESTS)/$(BINAIRE)/client.o: $(SOURCE)/client.cpp $(SOURCE)/client.h
	g++ -o $@ -c $<



# Enlève l'exécutable et les fichiers objets intermédiaires.
clean:
	rm -rf $(BINAIRE)/$(EXEC) $(BINAIRE)/*.o


