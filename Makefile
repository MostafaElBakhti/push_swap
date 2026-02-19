NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes

SRCS_DIR	= srcs

SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/operations/push.c \
			  $(SRCS_DIR)/operations/swap.c \
			  $(SRCS_DIR)/operations/rotate.c \
			  $(SRCS_DIR)/operations/reverse_rotate.c \
			  $(SRCS_DIR)/parsing/ft_atol.c \
			  $(SRCS_DIR)/parsing/parse_args.c \
			  $(SRCS_DIR)/parsing/validate.c \
			  $(SRCS_DIR)/sorting/cost.c \
			  $(SRCS_DIR)/sorting/execute.c \
			  $(SRCS_DIR)/sorting/position.c \
			  $(SRCS_DIR)/sorting/push_swap.c \
			  $(SRCS_DIR)/sorting/sort_small.c \
			  $(SRCS_DIR)/sorting/sort_turk.c \
			  $(SRCS_DIR)/sorting/target.c \
			  $(SRCS_DIR)/utils/free_stack.c \
			  $(SRCS_DIR)/utils/print_stack.c \
			  $(SRCS_DIR)/utils/stack_add_back.c \
			  $(SRCS_DIR)/utils/stack_last.c \
			  $(SRCS_DIR)/utils/stack_new.c \
			  $(SRCS_DIR)/utils/stack_size.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
