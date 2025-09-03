# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME    := libft.a
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -c

SRCS    := ft_isalpha.c     ft_isdigit.c        ft_isalnum.c       ft_isascii.c \
           ft_isprint.c     ft_strlen.c         ft_memset.c        ft_bzero.c \
           ft_memcpy.c      ft_memmove.c        ft_strlcpy.c       ft_strlcat.c \
           ft_toupper.c     ft_tolower.c        ft_strchr.c        ft_strrchr.c \
           ft_strncmp.c     ft_memchr.c         ft_memcmp.c        ft_strnstr.c \
           ft_atoi.c        ft_calloc.c         ft_strdup.c        ft_substr.c \
           ft_strjoin.c     ft_strtrim.c        ft_split.c         ft_itoa.c \
           ft_strmapi.c     ft_striteri.c       ft_putchar_fd.c    ft_putstr_fd.c \
           ft_putendl_fd.c  ft_putnbr_fd.c      ft_lstnew.c        ft_lstadd_front.c \
           ft_lstsize.c     ft_lstlast.c        ft_lstadd_back.c   ft_lstdelone.c \
           ft_lstclear.c    ft_lstiter.c        ft_lstmap.c        ft_lltoa.c \
           ft_uitoa.c       ft_uitoa_base.c     ft_ulltoa_base.c   ft_memtoa_base.c \
           ft_printf.c      ft_get_next_line.c  ft_get_next_line_utils.c

OBJTS   := $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJTS)
	ar rcs $(NAME) $(OBJTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

get_var:
	@echo $(OBJTS)

.PHONY: all clean fclean re get_var
