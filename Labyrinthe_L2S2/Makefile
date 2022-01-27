CFLAGS = -Wall -ansi -pedantic
LFLAGS = -lMLV

NAME = lab

$(NAME): ascii.o graphic.o MazeBlock.o parseur.o utf8.o union_find.o victor.o lab.o
	gcc -o $(NAME) $^ $(CFLAGS) $(LFLAGS)

lab.o: lab.c ascii.h graphic.h MazeBlock.h parseur.h victor.h union_find.h utf8.h
	gcc -c lab.c $(CFLAGS)

ascii.o: ascii.c ascii.h
	gcc -c ascii.c $(CFLAGS)

graphic.o: graphic.c graphic.h
	gcc -c graphic.c $(CFLAGS)

MazeBlock.o: MazeBlock.c MazeBlock.h
	gcc -c MazeBlock.c $(CFLAGS)

parseur.o: parseur.c parseur.h
	gcc -c parseur.c $(CFLAGS)

utf8.o: utf8.c utf8.h structures.h
	gcc -c utf8.c $(CFLAGS)

union_find.o: union_find.c union_find.h MazeBlock.h
	gcc -c union_find.c $(CFLAGS)

victor.o: victor.c victor.h MazeBlock.h
	gcc -c victor.c $(CFLAGS)