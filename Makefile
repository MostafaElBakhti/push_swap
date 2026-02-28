NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = push_swap.c \
       cost.c \
       position.c \
       sort_small.c \
       sort_turk.c \
       target.c \
       indexing.c \
       sort_utils.c \
       sort_rotations.c \
       push.c \
       reverse_rotate.c \
       rotate.c \
       swap.c \
       ft_atol.c \
       ft_split.c \
       parse_args.c \
       validate.c \
       free_stack.c \
       stack_add_back.c \
       stack_last.c \
       stack_new.c \
       stack_size.c \
       utils.c

OBJS = push_swap.o \
       cost.o \
       position.o \
       sort_small.o \
       sort_turk.o \
       target.o \
       indexing.o \
       sort_utils.o \
       sort_rotations.o \
       push.o \
       reverse_rotate.o \
       rotate.o \
       swap.o \
       ft_atol.o \
       ft_split.o \
       parse_args.o \
       validate.o \
       free_stack.o \
       stack_add_back.o \
       stack_last.o \
       stack_new.o \
       stack_size.o \
       utils.o

BONUS_SRCS = bonus/checker.c \
             bonus/checker_utils.c \
             bonus/get_next_line.c \
             bonus/get_next_line_utils.c \
             bonus/bonus_utils.c \
             bonus/op_bonus.c \
             bonus/parsing_bonus.c \
             bonus/parsing_utils.c \
             bonus/split_bonus.c \
             bonus/stack_bonus.c

BONUS_OBJS = bonus/checker.o \
             bonus/checker_utils.o \
             bonus/get_next_line.o \
             bonus/get_next_line_utils.o \
             bonus/bonus_utils.o \
             bonus/op_bonus.o \
             bonus/parsing_bonus.o \
             bonus/parsing_utils.o \
             bonus/split_bonus.o \
             bonus/stack_bonus.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus