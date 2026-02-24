NAME        := push_swap

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -Iincludes

SRC_DIR     := srcs
OBJ_DIR     := obj

SRCS_SRC := $(shell find $(SRC_DIR) -type f -name "*.c" ! -path "$(SRC_DIR)/parsing_practice/*")
SRCS_ROOT := cost.c position.c sort_small.c sort_turk.c target.c indexing.c sort_utils.c sort_rotations.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_SRC)) $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_ROOT))

RM          := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re