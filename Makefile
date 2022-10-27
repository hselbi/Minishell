# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 22:54:55 by hselbi            #+#    #+#              #
#    Updated: 2022/10/26 22:27:59 by hselbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = all clean fclean re

EXEC = $(addprefix exec/, main_execute.c execute.c execute_utils.c waitpid.c)

TOOLS = $(addprefix tools/, free_things.c utils.c signals.c errors.c)

PATH_BUILTIN = built-in/

BUILDIN = cd_built.c cd_built2.c envir_built.c export_built.c export_built2.c export_built3.c export_helper.c pwd_built.c unset_built.c echo_built.c exit_built.c built_in.c

PARSE = $(addprefix parsing/, an_other_file.c errors.c errors2.c expand.c ft_iitoa.c ft_split.c ft_strjoin.c get_next_line.c get_next_line_utils.c here_doc.c make_struct.c outils.c quotes.c redirection.c redirection2.c test_func.c test_pars.c)

WD = wildcard/wildcard_bonus.c wildcard/wildcard_utils1_bonus.c wildcard/wildcard_utils2_bonus.c

# /************************************************************/
SRC = main.c $(addprefix $(PATH_BUILTIN), $(BUILDIN)) $(PARSE) $(TOOLS) $(EXEC) $(WD) 

LIBFT = libft/libft.a

OBJ = $(SRC:%.c=%.o)

## work

RM = rm -rf

OBJ = $(SRC:.c=.o)

CC = gcc

RFLAGS = -lreadline -I /Users/hselbi/.brew/Cellar/readline/8.1.2/include/readline -L /Users/hselbi/.brew/Cellar/readline/8.1.2/lib

FLAGS = -Wall -Wextra -Werror

FSA_ADD = -g -fsanitize=address

NAME = minishell

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ) $(SRC)
	@echo "\033[0;93mMake $(NAME) ..."
	@$(MAKE) -C Libft
	@$(CC) $(FLAG) $(RFLAGS)  $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;92m$(NAME) is Done\033[0m"

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C Libft clean
	@echo "\033[1;91mCleaning Objects files is Done\033[0m"

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo "\033[1;91mCleaning is Done\033[0m"

re: fclean all
