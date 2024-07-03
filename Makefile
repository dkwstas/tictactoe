CC = gcc 
CFLAGS = -Wall -g
OBJ = main.o game.o screen.o msg.o

all: $(OBJ)
	$(CC) $(CFLAGS) *.o -o main -fsanitize=address

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $*.c -fsanitize=address

clean:
	$(RM) main
	$(RM) main.o
	$(RM) game.o
	$(RM) screen.o
	$(RM) msg.o
