# racourcis :
# $@ représente la cible
# $^ représente la liste des dépendances
# $< représente la première dépendance (la plus à gauche dans la liste)

# déclaration de variables
# le compilateur
CC = gcc
# les options de compilateur
CFLAGS = -g -Wall
# liste des programme à créer 
PROGRAMS = main

# premiere regle : liste des programme à compiler
# règle sans action, seulement aavec des dépendances 
all : $(PROGRAMS)

# règle pour compiler le main
# il faut mettre tous les noms des fichiers .o dans les dépendances
main : main.o 
	$(CC) $(CFLAGS) -o $@ $^
# règle générique de compilation des .o à partir des .c
%.o : %.c %h
	$(CC) $(CFLAGS) -c $<

# effacer les .o et les executables 
# pour executer cette regle il faut taper dans le termnal "make clean"
clean : 
	rm *.O $(PROGRAMS)