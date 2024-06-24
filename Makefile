NAME = pipex
CC = cc
CFLAGS = -Werror -Wall -Wextra
RM = rm -rf
SRCS_PATH = src
SRCS = 	pipex.c \
	$(SRCS_PATH)/utils_1.c\
	$(SRCS_PATH)/utils_2.c \
	$(SRCS_PATH)/get_path.c \
	$(SRCS_PATH)/error_handlers.c \
	$(SRCS_PATH)/ft_split.c 

OBJS = $(SRCS:%.c=%.o)


#Rule to build the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Phony targets
all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
