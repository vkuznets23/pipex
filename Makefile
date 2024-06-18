NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	pipex.c \
		utils_2.c \
		get_path.c \
		ft_split.c \

OBJS = $(SRCS:.c=.o)

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	$(RM) $(OBJS)

clean :
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
