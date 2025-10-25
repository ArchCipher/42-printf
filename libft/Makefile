# 			Library Name
NAME		= libft.a

#			Compiler & Flags
CC			= cc
FLAGS		= -Wall -Werror -Wextra

#			Headers
HEADER		= libft.h

#			Sources
MSRCS		= \
			isalpha isdigit isalnum isascii isprint toupper tolower\
			strlen strlcpy strlcat strchr strrchr strnstr strncmp\
			memset memcpy bzero memccpy memmove memchr memcmp\
			atoi strdup calloc
ASRCS		= \
			substr strjoin strtrim split itoa strmapi striteri\
			putchar_fd putstr_fd putendl_fd putnbr_fd 
ESRCS		= \
			isspace
BSRCS		= \
			lstnew lstadd_front lstsize lstlast lstadd_back\
			lstdelone lstclear lstiter lstmap

SRCS		= $(MSRCS) $(ASRCS) $(ESRCS)
MAN_SRCS	= $(addprefix ft_, $(addsuffix .c, $(SRCS)))
BONUS_SRCS	= $(addprefix ft_, $(addsuffix .c, $(BSRCS)))

#			Objects
MAN_OBJS	= $(MAN_SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

#			Rules
%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(MAN_OBJS)
			ar rcs $@ $^

#			Bonus with datestamp
bonus:		bonus.stamp
bonus.stamp:$(MAN_OBJS) $(BONUS_OBJS)
			ar rcs $(NAME) $^
			touch $@

clean:
			rm -f $(MAN_OBJS) $(BONUS_OBJS) bonus.stamp

fclean:		clean
			rm -f $(NAME) 

re:			fclean all bonus

.PHONY:		all bonus clean fclean re

#			$@	target name (left side of :)
#			$<	first prerequisite (right side of :)
#			$^	all prerequisites (right side of : (space separated))
#			$?	newer prerequisites (updated ones)
