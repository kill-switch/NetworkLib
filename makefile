INC = -I inc/
CC = gcc
SRC = src/
TEST = test/

.PHONY:clean
clean:
	@echo "All intermediate files have been removed"
	@rm -f *.o

test_netError:
	gcc -c $(SRC)neterror.c $(INC)
	gcc -c $(SRC)testneterror.c $(INC)
	gcc -o neterror.o testneterror.o $(INC)
