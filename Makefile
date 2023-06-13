CC = cc
LDFLAGS = -lreadline
MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = lib/libft

# List of source files
SRCS = ./src/main.c src/ft_lexer.c src/signals.c ./src/ft_cd.c ./src/env_utils.c ./src/ft_echo.c ./src/ft_pwd.c ./src/ft_export.c  ./src/utils.c ./src/print_sorted_env.c  ./src/ft_env.c ./src/ft_unset.c  \

# List of object files to build
OBJS = $(SRCS:.c=.o)

# Build executable
all: $(LIBFT_DIR)/libft.a $(MINISHELL)

# Build the client executable
$(MINISHELL): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $@

# Build the libft library
$(LIBFT_DIR)/libft.a: $(LIBFT_DIR)/src/*.c
	$(MAKE) -C $(LIBFT_DIR) all

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

# Remove object files and executables
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

# Remove object files, executables, and the libft library
fclean: clean
	$(RM) $(MINISHELL)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean re
