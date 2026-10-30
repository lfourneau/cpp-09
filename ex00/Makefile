# -*- Makefile -*-

CC=c++
FLAGS=-Wall -Wextra -Werror -std=c++98 -g
CPP=BitcoinExchange.cpp main.cpp
CO=$(CPP:.cpp=.o)
PROG=btc

all: $(PROG)

$(PROG): $(CO)
	$(CC) $(FLAGS) $(CO) -o $@ -g

%.o:%.cpp
	$(CC) $(FLAGS) $< -c -o $@ -g

clean:
	rm -rf $(CO)

fclean: clean
	rm -rf $(PROG)

re: fclean all

.PHONY: all clean fclean re 