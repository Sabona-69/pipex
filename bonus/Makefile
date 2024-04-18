# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabona <sabona@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 05:16:48 by hel-omra          #+#    #+#              #
#    Updated: 2024/04/12 08:54:25 by sabona           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex_b

CC			= cc

RM			= rm -rf

FLAGS		= -g -fsanitize=address#-Wall -Wextra -Werror

SRC			= pipex.c utils.c utils2.c errors.c 

OBJ			= $(SRC:.c=.o)

all			: $(NAME) clean

%.o			: %.c pipex.h
				$(CC) $(FLAGS) -c $< -o $@

$(NAME)		: $(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME)
clean		:
				$(RM) $(OBJ)

fclean		: clean
				$(RM) $(NAME)

re			: fclean all
