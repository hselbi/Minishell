# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 11:45:14 by hselbi            #+#    #+#              #
#    Updated: 2022/10/22 02:41:25 by hselbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =	libft.a

CC = gcc

FLAG = -Wall -Wextra -Werror  #-fsanitize=address -g

SRCS = 	ft_atoi.c\
		ft_bzero.c\
		ft_strncmp.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_split.c\
		ft_strchr.c\
		ft_strcpy.c\
		ft_strcat.c\
		ft_strdup.c\
		ft_calloc.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_substr.c\
	   	ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstsize_bonus.c


# bz
OBJS_SRCS = ${SRCS:%.c=%.o}

all: ${NAME} 

${NAME} : ${OBJS_SRCS} $(SRCS)
	@ar -rcs ${NAME} *.o

%.o : %.c
	@${CC} ${FLAG} -c $< 

fclean : clean
	@rm -rf ${NAME}

clean:
	@rm -rf ${OBJS_SRCS}

re : fclean all
