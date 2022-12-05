# déclaration de variables
# le compilateur
CC = gcc
# les options de compilateur
#-fsanitize=address
CCFLAGS = -g  -Wall -Wextra -c
COFLAGS = -g  -Wall -Wextra -o
# liste des programme à créer 
PROGRAMS = main

# premiere regle : liste des programme à compiler
# règle sans action, seulement avec des dépendances 
all : $(PROGRAMS)

# règle pour compiler le main
# il faut mettre tous les noms des fichiers .o dans les dépendances
main : main.o tests.o reader.o tools.o ethernet.o ipv4.o tcp.o http.o flowGraph.o
	$(CC) $(COFLAGS) main sources/bin/*.o -lm
main.o :   sources/main.c sources/headers/*.h
	$(CC) $(CCFLAGS) sources/main.c -o sources/bin/main.o
# règle générique de compilation des .o à partir des .c
%.o : sources/%.c 
	$(CC) $(CCFLAGS) $< -o sources/bin/$@
# effacer les .o et les executables 
# pour executer cette regle il faut taper dans le termnal "make clean"
clean : 
	rm -f sources/bin/*.o
	rm $(PROGRAMS)
