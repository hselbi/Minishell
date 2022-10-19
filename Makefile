
override CFLAGS += -Wall -D_FILE_OFFSET_BITS=64
override LDFLAGS += -lm
UNAME := $(shell uname)
PKG_CONFIG ?= pkg-config
ifeq ($(UNAME), Linux)
    ifeq (, $(shell which $(PKG_CONFIG) 2> /dev/null))
    $(error "pkg-config command not found")
    endif
    ifeq (, $(shell $(PKG_CONFIG) ncursesw --libs 2> /dev/null))
    $(error "ncurses package not found")
    endif
    override LDFLAGS += $(shell $(PKG_CONFIG) ncursesw --libs)
endif
ifeq ($(UNAME), Darwin)
    override LDFLAGS += -lncurses
endif
ifeq ($(UNAME), FreeBSD)
    override LDFLAGS += -lncurses -lprocstat
endif

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

FSA_ADD = -g3 -fsanitize=address

# -fno-omit-frame-pointer : a nice stack traces in error messages

NAME = minishell

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ) $(SRC)
	@echo "\033[0;93mMake $(NAME) ..."
	@$(MAKE) -C Libft
	@$(CC) $(FLAG) $(RFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;92m$(NAME) is Done\033[0m"

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C Libft clean
	@echo "\033[1;91mclean *.o is Done\033[0m"

fclean: clean
	@$(RM) $(NAME) $(LIBFT)
	@echo "\033[1;91mclean is Done\033[0m"

re: fclean all
