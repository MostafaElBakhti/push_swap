NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = checker.c \
		checker_utils.c \
		bonus_utils.c \
		op_bonus.c \
		split_bonus.c \
		parsing_bonus.c \
		parsing_utils.c \
		stack_bonus.c \
		get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re