TARGET = main.c graphique.c console.c


CC = gcc
CFLAGS = -g02 -Wall -Wextra
DEBUG = -g -Wall -Wextra
EXE = grilleEntiers
LIB = -lMLV

all:
	$(CC) $(CFLAGS) $(TARGET) -o $(EXE) $(LIB)

debug:
	$(CC) $(DEBUG) $(TARGET) -o $(EXE) $(LIB)

clean: -rm -rf $(EXE)