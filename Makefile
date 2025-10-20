# If your project allows you to use your libft, you must copy its sources and its
# associated Makefile into a libft folder. Your project’s Makefile must compile
# the library by using its Makefile, then compile the project.

# Turn in files Makefile, *.h, */*.h, *.c, */*.c

#			Library and Project names
NAME		= libftprintf.a
LIBDIR		= ../libft
LIBNAME		= $(LIBDIR)/libft.a

#			Compiler and Flags
CC			= cc
FLAGS		= -Wall -Werror -Wextra
SFLAGS		= -fsanitize=address

#			Headers
ALL_HEADERS	= -I. -I$(LIBDIR)

#			Sources & Objects
MSRCS = \
	   printf printf_utils
SRCS = $(addprefix ft_, $(addsuffix .c, $(MSRCS)))
OBJS	= $(SRCS:.c=.o)
LIBOBJS = $(wildcard $(LIBDIR)/*.o)

# BSRCS = \
# BONUS_SRCS = $(addprefix ft_, $(addsuffix .c, $(BSRCS)))
# BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) $(ALL_HEADERS) -c $< -o $@

all: $(LIBNAME) $(NAME)

$(LIBNAME):
	$(MAKE) bonus -C $(LIBDIR)

$(NAME): $(OBJS) $(LIBOBJS)
	ar rcs $@ $^

test: $(NAME)
	$(CC) $(FLAGS) -g $(ALL_HEADERS) $(SRCS) $(LIBNAME) $(NAME) -o a.out
	./a.out

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all lib clean fclean test