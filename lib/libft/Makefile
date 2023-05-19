# Colors for pretty printing
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

LIBFT = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/ft_isalnum.c    src/ft_isprint.c   src/ft_memcmp.c\
	   src/ft_strlcat.c    src/ft_strncmp.c   src/ft_substr.c\
	   src/ft_atoi.c       src/ft_isalpha.c   src/ft_memcpy.c\
	   src/ft_strchr.c     src/ft_strlcpy.c   src/ft_strnstr.c\
	   src/ft_tolower.c    src/ft_bzero.c     src/ft_isascii.c\
	   src/ft_memmove.c    src/ft_strdup.c    src/ft_strlen.c\
	   src/ft_strrchr.c    src/ft_toupper.c   src/ft_calloc.c\
	   src/ft_isdigit.c    src/ft_memchr.c    src/ft_memset.c\
	   src/ft_strjoin.c    src/ft_strtrim.c   src/ft_split.c\
	   src/ft_itoa.c       src/ft_strmapi.c   src/ft_striteri.c\
	   src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putendl_fd.c\
	   src/ft_putnbr_fd.c  src/ft_lstclear.c  src/ft_printf.c\
	   src/ft_putstr.c     src/ft_putptr.c    src/ft_putnbr.c\
	   src/ft_puthex.c     src/ft_putchar.c   src/ft_intlen.c\
	   src/ft_putstrrev.c  src/ft_find_type.c src/ft_long_itoa.c\
	   src/get_next_line.c src/ft_lstnew.c    src/ft_lstadd_front.c\
	   src/ft_lstsize.c    src/ft_lstlast.c   src/ft_lstadd_back.c\
	   src/ft_lstdelone.c  src/ft_lstclear.c  src/ft_lstclear.c\
	   src/ft_lstiter.c    src/ft_lstmap.c    src/ft_lstnew.c

HEADERS := -I inc
OBJS := $(SRCS:.c=.o)

# Targets
all: $(LIBFT)

$(LIBFT): $(OBJS)
	@echo "$(YELLOW)Building $(LIBFT)...$(NC)"
	@ar rcs $(LIBFT) $(OBJS)
	@echo "$(GREEN)$(LIBFT) is ready!$(NC)"

%.o: %.c
	@$(CC) -c $^ -o $@ $(FLAGS) $(HEADERS)
	@echo "$(YELLOW)Compiling $^...$(NC)"

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(YELLOW)Cleaning $(LIBFT)...$(NC)"
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
