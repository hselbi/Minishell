.PHONY = all clean fclean re

EXEC = $(addprefix exec/, execute.c execute_utils.c waitpid.c)

TOOLS = $(addprefix tools/, free_things.c utils.c signals.c)

PATH_BUILTIN = built-in/

BUILDIN = cd_built.c envir_built.c export_built.c export_built2.c export_built3.c pwd_built.c unset_built.c echo_built.c exit_built.c built_in.c

PARSE = $(addprefix parsing/, errors.c errors2.c expand.c ft_iitoa.c ft_split.c ft_strjoin.c get_next_line.c get_next_line_utils.c here_doc.c make_struct.c outils.c quotes.c redirection.c redirection2.c test_func.c test_pars.c)

PATH_PRINT = $(addprefix print_for_debug/, print_pars.c)

WD = wildcard/wildcard.c wildcard/wildcard_utils1.c wildcard/wildcard_utils2.c

# /************************************************************/
SRC = main.c $(addprefix $(PATH_BUILTIN), $(BUILDIN)) $(PARSE) $(PATH_PRINT) $(TOOLS) $(EXEC) $(WD) 

LIBFT = libft/libft.a

OBJ = $(SRC:%.c=%.o)


## work

RM = rm -rf

OBJ = $(SRC:.c=.o)

CC = gcc

RFLAGS = -lreadline -I /Users/hselbi/.brew/Cellar/readline/8.1.2/include/readline -L /Users/hselbi/.brew/Cellar/readline/8.1.2/lib

FLAGS = -Wall -Wextra -Werror

FSA_ADD = -g -fsanitize=address 

# -fno-omit-frame-pointer : a nice stack traces in error messages

NAME = minishell

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ) $(SRC)
	@$(MAKE) -C Libft
	@$(CC) $(FLAG) $(FSA_ADD) $(RFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C Libft clean

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

re: fclean all
