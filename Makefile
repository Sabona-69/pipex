# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 05:16:48 by hel-omra          #+#    #+#              #
#    Updated: 2024/05/05 21:45:22 by hel-omra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

BNAME		= pipex_b

CC			= cc

RM			= rm -rf

FLAGS		= -Wall -Wextra -Werror

SRC			= mandatory/pipex.c mandatory/utils.c mandatory/utils2.c mandatory/utils3.c

B_SRC		= bonus/pipex_b.c bonus/utils_b.c bonus/utils2_b.c bonus/utils3_b.c bonus/get_next_line.c

OBJ			= $(SRC:.c=.o)

BOBJ		= $(B_SRC:.c=.o)

all			: $(NAME)

bonus		: $(BNAME)

mandatory/%.o: mandatory/%.c include/pipex.h
				$(CC) $(FLAGS) -c $< -o $@

bonus/%.o	: bonus/%.c include/pipex_b.h
				$(CC) $(FLAGS) -c $< -o $@

$(NAME)		: $(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(BNAME)		: $(BOBJ)
				$(CC) $(FLAGS) $(BOBJ) -o $(BNAME)				
clean		:
				$(RM) $(OBJ) $(BOBJ)

fclean		: clean
				$(RM) $(NAME) $(BNAME)

re			: fclean all
