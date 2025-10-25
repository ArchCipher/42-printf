#add header for all files

#			Library and Project names
NAME		= libftprintf.a

#			Compiler and Flags
CC			= cc
FLAGS		= -Wall -Werror -Wextra
SFLAGS		= -fsanitize=address

#			Headers
ALL_HEADERS	= -I.

#			Sources & Objects
MSRCS = \
	   printf parser print_types print_int printf_utils
SRCS = $(addprefix ft_, $(addsuffix .c, $(MSRCS)))
OBJS	= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) $(ALL_HEADERS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

bonus: $(NAME)

test: $(NAME)
	$(CC) $(FLAGS) -g $(ALL_HEADERS) $(SRCS) $(NAME) main.c -o a.out
	./a.out | cat -e

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean test