NAME        := push_swap

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -Iincludes

SRC_DIR     := srcs
OBJ_DIR     := obj

# Find all .c files in srcs/, excluding srcs/parsing_practice/
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c" ! -path "$(SRC_DIR)/parsing_practice/*") indexing.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

RM          := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile .c -> .o into obj/ mirroring srcs/ structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re