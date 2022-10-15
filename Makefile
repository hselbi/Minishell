.PHONY = all clean fclean re

EXEC = $(addprefix exec/, execute.c execute_utils.c waitpid.c)

TOOLS = $(addprefix tools/, free_things.c utils.c signals.c)

PATH_BUILTIN = built-in/

BUILDIN = cd_built.c envir_built.c export_built.c export_built2.c export_built3.c pwd_built.c unset_built.c echo_built.c exit_built.c built_in.c

PATH_PRINT = $(addprefix print_for_debug/, print_pars.c)

WD = wildcard/wildcard.c wildcard/wildcard_utils1.c wildcard/wildcard_utils2.c

# /************************************************************/
SRC = main.c $(addprefix $(PATH_BUILTIN), $(BUILDIN)) $(PATH_PRINT) $(TOOLS) $(EXEC) $(WD)

LIBFT = libft/libft.a

PARSE = minishell_parsing/parse.a

OBJ = $(SRC:%.c=%.o)


## work

RM = rm -rf

OBJ = $(SRC:.c=.o)

CC = gcc

RFLAGS = -lreadline -I /Users/hselbi/.brew/Cellar/readline/8.1.2/include/readline -L /Users/hselbi/.brew/Cellar/readline/8.1.2/lib

FLAGS = -Wall -Wextra -Werror

FSA_ADD = -fsanitize=address -g

# -fno-omit-frame-pointer : a nice stack traces in error messages

NAME = minishell

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ) $(SRC)
	@$(MAKE) -C Libft
	@$(MAKE) -C minishell_parsing
	@$(CC) $(FLAG) $(FSA_ADD) $(RFLAGS) $(OBJ) $(LIBFT) $(PARSE) -o $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C Libft clean
	@$(MAKE) -C minishell_parsing clean

fclean: clean
	@$(RM) $(NAME) $(LIBFT) $(PARSE)

re: fclean all
