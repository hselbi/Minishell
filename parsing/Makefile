# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 14:47:37 by aerrazik          #+#    #+#              #
#    Updated: 2022/10/16 23:16:30 by hselbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

GCF = -Wall -Wextra -Werror -g3 -g -fsanitize=address

NAME = parse.a

SRC = outils.c test_pars.c ft_split.c ft_strjoin.c test_func.c get_next_line.c \
		get_next_line_utils.c here_doc.c expand.c redirection.c quotes.c \
		errors.c ft_iitoa.c errors2.c make_struct.c redirection2.c

OBJS = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $(NAME) *.o
	@rm -rf $(OBJS)

%.o:%.c
	@$(CC) $(GCF) -c $<

clean :
	@rm -rf ${OBJS}

fclean : clean
	@rm -rf ${NAME}

re : fclean all
