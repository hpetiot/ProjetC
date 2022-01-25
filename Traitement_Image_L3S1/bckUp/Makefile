CC=gcc
CFLAGS= -Wall -ansi
LDFLAGS= -lMLV
SRC=./sources/
INC=./includes/
EXEC=test

$(EXEC): main.o window.o button.o quadtree.o
	$(CC) $^ -o $(EXEC) $(CFLAGS) $(LDFLAGS)

main.o: $(SRC)main.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

window.o: $(SRC)window.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

button.o: $(SRC)button.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

quadtree.o: $(SRC)quadtree.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o
	rm $(EXEC)
