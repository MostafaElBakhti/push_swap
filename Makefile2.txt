NAME = push_swap
CHECKER = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = push_swap.c cost.c position.c sort_small.c sort_turk.c target.c indexing.c sort_utils.c sort_rotations.c \
	  push.c reverse_rotate.c rotate.c swap.c ft_atol.c ft_split.c parse_args.c validate.c \
	  free_stack.c stack_add_back.c stack_last.c stack_new.c stack_size.c utils.c

CHECKER_SRC = bonus/checker.c bonus/checker_utils.c \
			  bonus/get_next_line.c bonus/get_next_line_utils.c

OBJ = $(SRC:.c=.o)
CHECKER_OBJ = $(CHECKER_SRC:.c=.o)

all: $(NAME) 

bonus: $(CHECKER)

$(CHECKER): bonus/get_next_line.h

$(NAME): $(OBJ) push_swap.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all