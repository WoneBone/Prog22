#compiler
CC = gcc
#compile flags (in the valgrind debugging stage the flag -ggdb3 was also being used
CFLAGS  = -Wall -g
#executable
default: palavras
#Linking
palavras:  main.o modo_1.o modo_2.o pc_play.o define_board.o play_book.o
	$(CC) $(CFLAGS) -o palavras  main.o modo_1.o modo_2.o pc_play.o define_board.o play_book.o
#Compilation of the object files 
main.o: main.c libhead.h
	$(CC) $(CFLAGS) -c main.c libhead.h
modo_1.o: modo_1.c libhead.h
	$(CC) $(CFLAGS) -c modo_1.c libhead.h
modo_2.o: modo_2.c libhead.h
	$(CC) $(CFLAGS) -c modo_2.c libhead.h
pc_play.o: pc_play.c libhead.h
	$(CC) $(CFLAGS) -c pc_play.c libhead.h
define_board.o: define_board.c libhead.h
	$(CC) $(CFLAGS) -c define_board.c libhead.h
play_book.o: play_book.c libhead.h
	$(CC) $(CFLAGS) -c play_book.c libhead.h
