CC = cc
MINITEST = miniTest
CFLAGS = -Wall -Wextra -Werror

# List of source files
SRCS = ./main.c ./get_next_line.c ./prompt.c ./source.c \

# List of object files to build
OBJS = $(SRCS:.c=.o)

# Build executable
all: $(MINITEST)

# Build the client executable
$(MINITEST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

# Remove object files and executables
clean:
	$(RM) $(OBJS)

# Remove object files, executables, and the libft library
fclean: clean
	$(RM) $(MINITEST)

# Rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean re
