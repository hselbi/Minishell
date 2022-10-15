#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "minishell_parsing/parser.h"
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
#include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/**************************************************************************
*				*      structures types    *
***************************************************************************/
/*			for wildcard			*/

typedef struct s_wild {
	char			*str;
	int				type;
	struct s_wild	*next;
	struct s_wild	*prev;
}			t_wild;

/*		i dont think that i need this one		*/

typedef struct s_cmd
{
	struct s_cmd	*args;
	char			*com;
	int				ft_input;
	int				ft_output;
	struct s_cmd	*next;
}	t_cmd;

/* global variable for code status exit */
/******************************/
int			g_status;
/******************************/

/*		i dont think that i need this one		*/

typedef struct s_mish //MIniSHell
{
	int		ind;
	char	*line;
	t_list	*envi;

}	t_mish;

/*		main structs that need to pass everything		*/

typedef struct s_mcmd //Minishell CoMmanD
{
	t_list	*en;
	t_list	*exp_en;
	char	**av;
	char	**spl_str;
	char	*home;
	char	*path;
	char	*cd;
	int		ac_spl;
	int		pid;
	int		fd[2];
	int		ac;
	int		in;
	int		out;
	int		index;
	int		d;
	t_pars	pars;

}	t_mcmd;

void	rl_replace_line(const char *text, int clear_undo);

/**************************************************************************
*				*      before action    *
***************************************************************************/

void	init_minishell(t_mcmd *command, char **envp);

/**************************************************************************
* 					*          built-ins      *							  
***************************************************************************/

//	main check for the building

int		buildin_cmd(t_mcmd *command, int i, int fd);
int		ft_builtin(t_mcmd *command, int fd);

// envp
t_list	*ft_env(char **en);
//check if first arg is "env" or "env "
void	my_env(t_mcmd *command);
//check if numbers of args is more then one or not

//	export
char	*with_equal(char *str, char **spl_str);
char	*without_equal(int i, char *arr, char **spl_str);
void	assemebly_str(char *lst, int fd);
void	fix_list(t_list *notComp, int fd);
int		check_eq(char *str);
int		many_eq(char *str);
char	**make_env(int i, char *lst);
void	exp_sorting(t_list *en, int fd);
void	new_export(t_mcmd *command);
void	sel_env(char *s, t_list **en);
int		check_av(char *av);

//	exit
void	my_exit(int ac, char **av);
void	exit_args(int ac, char *av[], int status);
int		is_digit(char *str);

// echo
void	my_echo(char *str[], int fd, int flag);
void	without_option(int fd, char *str[], int i, int flag);
void	with_option(int fd, char *str[], int i, int flag);
int		check_option(char *str);

// cd
int		init_cd(t_mcmd *command, int i);
void	my_cd(t_mcmd *command, int i);
char	*cd_arg(t_mcmd *command, int i, char *buf);
int		ft_check_cd(char *av);
int		check_ch(char c1, char c2);

// unset
void	init_unset(t_mcmd *command);
int		check_var(char *str, t_list *en);
t_list	*my_unset(int ac, char **av, t_list *en);

// pwd
int		ft_pwd(t_mcmd *command, int fd);
void	adding_newpath(t_mcmd *command, char *new_path);

/**************************************************************************
*						*		execution		*
***************************************************************************/
// execute_utils.c

void	is_cmd_path(char **path, char *cmd, char *en[]);
char	*correct_one(char **paths, char *cmd);
char	*make_path(char *cmd, char *en[]);
void	ft_excusion(char *cmd, t_mcmd *command, char *en[]);

// execute.c

void	exec(t_mcmd *command, char *str, t_list *en);
int		ft_exec(t_mcmd *command);
char	**en_conv(t_list *envp);
void	redirect(t_pars *arr, t_mcmd *command);

//	waitpid.c

void	ft_waitpid(t_mcmd *command);
int		status_child(int pid);

/**************************************************************************
* 						*		tools		*
***************************************************************************/

int		check_char(char c1, char c2);
void	ft_free(char **str);
void	list_free(t_list *command);

// void	handle_signal(int signum);
void	free_two(char **str, int i);
void	sig_handler(int sig);
// void	void_sig(int sig);
void	void_sig2(int sig);

int		ft_strcmp(char *s1, char *s2);

int		spaces_check(char *str);
void	ft_print_pars(t_pars *pars);

int		isspaces(char *str);

/**************************************************************************
* 				*		printing for debuging		*
***************************************************************************/

void	exp_envp(t_list *list, int fd, int flag);
int		is_built(char *str);
int		is_valid(char *check, char *mesure);
void	args_pars(t_pars pars);

/**************************************************************************
* 					*          parsing			*							  
***************************************************************************/

void	pars_free(t_pars *p);
void	p_free(t_mcmd *command);
void	struct_free(t_mcmd *command);
void	print_struct(t_mcmd *commmad);
void	lst_clear(t_mcmd **lst, void (*del)(void*));

/**************************************************************************
* 					*          wildcard		      *					
***************************************************************************/

int		size_dir(void);
char	**files_tab(int len);
char	*wc_handle(char *line);
char	*ast_replace(char *line, int i);
int		finish_finder(char *str, int i);
int		start_finder(char *str, int i);
int		suffix_check(char *str, char *su);
char	*suffix(char *str);
char	*prefix(char *str);
char	*ft_strdup2(char *str);
char	*strjoin_free(char *s1, char const *s2);
char	*wc_parser(char *str, int i, char *out, char **arr);
void	free_ast(char *pre, char *su, char **arr);

#endif // MINISHELL_H
