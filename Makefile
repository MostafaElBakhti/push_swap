# === Project Names ===
NAME        := push_swap
BONUS_NAME  := checker

# === Compiler Settings ===
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -I.

# === Directories ===
SRC_DIR     := srcs
OBJ_DIR     := obj

# === push_swap sources ===
SRCS        := push_swap.c cost.c position.c sort_small.c sort_turk.c target.c indexing.c sort_utils.c sort_rotations.c \
               push.c reverse_rotate.c rotate.c swap.c ft_atol.c ft_split.c parse_args.c validate.c \
               free_stack.c stack_add_back.c stack_last.c stack_new.c stack_size.c utils.c

OBJS        := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# === Bonus checker sources ===
# Exclude push_swap.c from bonus sources to avoid duplicate main
BONUS_SRCS  := bonus/checker.c bonus/checker_utils.c bonus/get_next_line.c bonus/get_next_line_utils.c \
               $(filter-out push_swap.c,$(SRCS))

BONUS_OBJS  := $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

# === Remove files ===
RM          := rm -rf

# === Default target ===
all: $(NAME)

# === Build push_swap ===
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# === Object compilation rules ===
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Bonus object compilation ===
$(OBJ_DIR)/bonus/%.o: bonus/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Build checker bonus ===
bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

# === Clean objects ===
clean:
	$(RM) $(OBJ_DIR)

# === Clean objects + executables ===
fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

# === Rebuild all ===
re: fclean all

.PHONY: all clean fclean re bonus