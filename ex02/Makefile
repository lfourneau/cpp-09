# -*- Makefile -*-

CC=c++
FLAGS=-Wall -Wextra -Werror -std=c++98 -g
CPP=PmergeMe.cpp main.cpp
CO=$(CPP:.cpp=.o)
PROG=PmergeMe

all: $(PROG)

$(PROG): $(CO)
	$(CC) $(FLAGS) $(CO) -o $@

%.o:%.cpp
	$(CC) $(FLAGS) $< -c -o $@

clean:
	rm -rf $(CO)

fclean: clean
	rm -rf $(PROG)

re: fclean all

.PHONY: all clean fclean re 