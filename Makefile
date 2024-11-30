CC = gcc
CFLAGS = -O3
WFLAGS = -Wall -Werror -Wextra -Wunreachable-code -Wpedantic
COMPILE = $(CC) $(CFLAGS) $(WFLAGS)

NAME = cvec
SRC = cvec.c
HEADER = cvec.h
OBJ = cvec.o
UTESTS_SRC = utests.c
UTESTS = utests 

test: re
	@$(COMPILE) -o $(UTESTS) $(UTESTS_SRC) $(SRC)
	@./utests

clean:
	@rm -rf *.o *.d utests *.out

fclean: clean
	@rm -rf $(NAME);

re: fclean

.PHONY: test clean fclean re
