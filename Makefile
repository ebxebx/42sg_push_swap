NAME      = push_swap
TEST_CMD = ./$(NAME) 1 2 3 -100 -1000
# TEST_CMD = ./$(NAME) 9 1 -10 -2 5 100

LIBFT_DIR = ./libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRCS = push_swap.c push_swap_utils.c move_stack.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Add dependency flags and derived files
DEPFLAGS = -MMD -MP
DEPS = $(SRCS:.c=.d)

all: $(NAME)

test: $(NAME) $(LIBFT)
	$(TEST_CMD)

test2: $(NAME) $(LIBFT)
	valgrind --leak-check=full $(TEST_CMD)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# The Pattern Rule. 
%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# include dependency files if they exist (don't error on first run)
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
