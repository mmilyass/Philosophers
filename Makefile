CC = cc 
NAME = philo

CFLAGS = -Wall -Wextra -Werror  #-fsanitize=thread -pthread -g

SRC = helpers.c\
	parsing.c \
	main.c \
	routine.c \
	eat_locks.c \
	checkers.c \
	is_doing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc  $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re

.SECONDARY: $(OBJ)
