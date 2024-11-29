NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

SRCS = parsing.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
		$(CC) $(FLAGS) -c $< -o $(<:.c=.o) -I includes 

all : $(NAME)

$(NAME): $(OBJS)
			make -C $(LIBFT)
			$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean : clean
				$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re