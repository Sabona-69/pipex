# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 05:16:48 by hel-omra          #+#    #+#              #
#    Updated: 2024/05/02 23:05:07 by hel-omra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= cc

RM			= rm -rf

FLAGS		= -Wall -Wextra -Werror

SRC			= pipex.c utils.c utils2.c utils3.c 

OBJ			= $(SRC:.c=.o)

all			: $(NAME)

%.o			: %.c pipex.h
				$(CC) $(FLAGS) -c $< -o $@

$(NAME)		: $(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME)
clean		:
				$(RM) $(OBJ)

fclean		: clean
				$(RM) $(NAME)

re			: fclean all
