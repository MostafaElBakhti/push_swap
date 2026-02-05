NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = srcs/main.c \
	srcs/operations/swap.c \
	srcs/operations/push.c \
	srcs/operations/rotate.c \
	srcs/operations/reverse_rotate.c \
	srcs/utils/stack_new.c \
	srcs/utils/stack_add_back.c \
	srcs/utils/stack_size.c \
	srcs/utils/stack_last.c \
	srcs/utils/print_stack.c \
	srcs/utils/free_stack.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✓ Compiled!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all