# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 05:16:48 by hel-omra          #+#    #+#              #
#    Updated: 2024/04/20 19:32:15 by hel-omra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex_b

CC			= cc

RM			= rm -rf

FLAGS		= -g -fsanitize=address#-Wall -Wextra -Werror

SRC			= pipex.c utils.c utils2.c utils3.c 

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
