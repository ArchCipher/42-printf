#add header for all files

#			Library and Project names
NAME		= libftprintf.a
DPRINTF_LIB	= libftdprintf.a
LIB_DIR		= ../ft_dprintf/

#			Compiler and Flags
CC			= cc
FLAGS		= -Wall -Werror -Wextra
SFLAGS		= -fsanitize=address

#			Headers
ALL_HEADERS	= -I$(LIB_DIR) -I.

#			Sources & Objects
SRCS = ft_printf.c
OBJS	= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) $(ALL_HEADERS) -c $< -o $@

all: lib $(NAME)

lib:
	@make -C $(LIB_DIR)

$(NAME): $(OBJS)
	@cp $(LIB_DIR)$(DPRINTF_LIB) $@
	ar r $@ $(OBJS)

test: lib $(NAME)
	$(CC) $(FLAGS) -g $(ALL_HEADERS) main.c $(NAME) -o a.out
	./a.out | cat -e

clean:
	rm -f $(OBJS)
	@make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean test lib