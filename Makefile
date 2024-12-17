NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

SRCS = parsing.c main.c utils.c philo.c init_struct.c

OBJS = $(SRCS:.c=.o)

# regle principale
all: $(NAME)

# regle pour creer l executable -fsanitize=thread -g
$(NAME): $(OBJS)
			$(CC) $(OBJS) -o $(NAME)

# regle pour creer les fichiers .o
.c.o:
		$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re