CC = cc
LDFLAGS = -lreadline
MINISHELL = minishell
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = lib/libft

# List of source files
SRCS = ./src/main.c src/ft_lexer.c src/signals.c ./src/ft_cd.c ./src/env_utils.c ./src/ft_echo.c \
./src/ft_pwd.c ./src/ft_export.c  ./src/utils.c ./src/print_sorted_env.c  ./src/ft_env.c ./src/ft_unset.c  \
./src/create_processes.c ./src/read_input.c ./src/count_strs.c ./src/special_split.c ./src/append_token.c  \
./src/execute_process.c ./src/word_butcher.c ./src/get_words_count.c ./src/check_quotes.c ./src/word_split.c \
./src/parser.c ./src/find_cmd.c ./src/parser_utils.c ./src/update_tokens.c ./src/find_args.c \
./src/find_redirs.c ./src/add_group.c ./src/add_group_utils.c ./src/create_redirects.c ./src/execute_cmd.c \
./src/heredoc.c ./src/destroy_processes.c ./src/get_directory_from_path_variable.c ./src/check_if_file_exists.c \

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
