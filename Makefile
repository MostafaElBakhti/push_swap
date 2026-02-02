NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -g


all: $(NAME)

$(NAME): main.c
	$(CC) $(CFLAGS) main.c -o $(NAME)
	@echo "✓ Compiled!"


clean:
	rm -f $(NAME)

fclean: clean


re: fclean all