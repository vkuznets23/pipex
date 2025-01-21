# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:44:34 by vkuznets          #+#    #+#              #
#    Updated: 2024/07/10 15:40:54 by vkuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Werror -Wall -Wextra
SRCS_PATH = src

SRCS = 	$(SRCS_PATH)/pipex.c \
	$(SRCS_PATH)/exec_utils.c \
	$(SRCS_PATH)/printing_utils.c\
	$(SRCS_PATH)/libft_utils.c \
	$(SRCS_PATH)/get_path.c \
	$(SRCS_PATH)/error_handlers.c \
	$(SRCS_PATH)/ft_split.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)
	@touch .mandatory

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(B_OBJS)
	@rm -f .mandatory

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
