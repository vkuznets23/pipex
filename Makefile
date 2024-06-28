# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 09:44:34 by vkuznets          #+#    #+#              #
#    Updated: 2024/06/28 09:46:22 by vkuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Werror -Wall -Wextra
SRCS_PATH = src
B_SRCS_PATH = src_bonus

SRCS = 	pipex.c \
	$(SRCS_PATH)/exec_utils.c \
	$(SRCS_PATH)/printing_utils.c\
	$(SRCS_PATH)/libft_utils.c \
	$(SRCS_PATH)/get_path.c \
	$(SRCS_PATH)/error_handlers.c \
	$(SRCS_PATH)/ft_split.c 

B_SRCS = $(B_SRCS_PATH)/pipex_bonus.c \
	$(B_SRCS_PATH)/last_child.c \
	$(SRCS_PATH)/exec_utils.c \
	$(SRCS_PATH)/printing_utils.c\
	$(SRCS_PATH)/libft_utils.c \
	$(SRCS_PATH)/get_path.c \
	$(SRCS_PATH)/error_handlers.c \
	$(SRCS_PATH)/ft_split.c 

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

all : mandatory

mandatory : .mandatory

.mandatory : $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)
	@touch .mandatory
	@rm -f .bonus

bonus : .bonus

.bonus : $(B_OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(B_OBJS)
	@touch .bonus
	@rm -f .mandatory

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(B_OBJS)
	@rm -f .bonus .mandatory

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
