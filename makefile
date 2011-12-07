INC = inc/
INCFLAG = -I $(INC)
CC = gcc
SRC = src/
TEST = test/

.PHONY:clean
clean:
	@echo "All intermediate files have been removed"
	@rm -f *.o

.PHONY:cleanTemps
cleanTemps:
	@echo "All temporary files will be removed"
	@rm -f $(SRC)*.*~ $(TEST)*.*~ $(INC)*.*~ *~

test_netError:
	@gcc -c $(SRC)neterror.c $(INCFLAG)
	@gcc -c $(TEST)testneterror.c $(INCFLAG)
	@gcc -o testneterror neterror.o testneterror.o $(INCFLAG)
	@./testneterror
	@rm -f testneterror
	@make clean
