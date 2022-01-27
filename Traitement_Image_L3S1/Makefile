CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lMLV -lm

SRC =./src/
INC =./includes/

EXEC = Projet
OBJ = main.o color.o create_quadtree.o decoding.o encoding.o list_errors.o minimisation.o pixel.o quadtree.o zone.o window.o button.o io.o decoding_graph.o encoding_graph.o bit_buffer.o

####################################################################################

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	mv ./$(OBJ) ./bin/

main.o: $(SRC)main.c $(INC)color.h $(INC)create_quadtree.h $(INC)decoding.h $(INC)decoding_graph.h $(INC)encoding.h $(INC)encoding_graph.h $(INC)list_errors.h $(INC)minimisation.h $(INC)quadtree.h 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

window.o: $(SRC)window.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

button.o: $(SRC)button.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

io.o: $(SRC)io.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

bit_buffer.o: $(SRC)bit_buffer.c 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

color.o: $(SRC)color.c $(INC)color.h $(INC)pixel.h $(INC)quadtree.h $(INC)zone.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

create_quadtree.o: $(SRC)create_quadtree.c $(INC)create_quadtree.h $(INC)color.h $(INC)list_errors.h $(INC)quadtree.h $(INC)zone.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

decoding.o: $(SRC)decoding.c $(INC)decoding.h $(INC)quadtree.h $(INC)bit_buffer.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

decoding_graph.o: $(SRC)decoding_graph.c $(INC)decoding_graph.h $(INC)decoding.h $(INC)quadtree.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

encoding.o: $(SRC)encoding.c $(INC)encoding.h $(INC)quadtree.h $(INC)bit_buffer.h $(INC)bit_buffer.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

encoding_graph.o: $(SRC)encoding_graph.c $(INC)encoding_graph.h $(INC)quadtree.h 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

list_errors.o: $(SRC)list_errors.c $(INC)list_errors.h $(INC)quadtree.h $(INC)zone.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)D

minimisation.o: $(SRC)minimisation.c $(INC)minimisation.h $(INC)color.h $(INC)quadtree.h 
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)D

pixel.o: $(SRC)pixel.c $(INC)pixel.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

quadtree.o: $(SRC)quadtree.c $(INC)quadtree.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

zone.o: $(SRC)zone.c $(INC)zone.h
	$(CC) -c $^ -I$(INC) $(CFLAGS) $(LDFLAGS)

####################################################################################

clean:
	rm -f *.o
	rm -f ./bin/*.o
	rm -f $(EXEC)
	rm -f $(INC)*.h.gch