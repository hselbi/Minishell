/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:54:52 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 21:49:14 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "parsing/parser.h"
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <sys/stat.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>

/**************************************************************************
*				*      structures types    *
***************************************************************************/

/* global variable for code status exit */
/******************************/
int			g_status;
/******************************/

/*		for readline		*/

typedef struct s_mish
{
	char	*line;

}	t_mish;

/*		main structs that need to pass everything		*/

typedef struct s_mcmd
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
*						*      before action    *
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
void	my_env(t_mcmd *command);

//	export
char	*with_equal(char *str, char **spl_str);
char	*without_equal(int i, char *arr, char **spl_str);
void	assemebly_str(char *lst, int fd, int flag);
void	fix_list(t_list *notComp, int fd, int flag);
int		check_eq(char *str);
int		many_eq(char *str);
char	**make_env(int i, char *lst);
void	exp_sorting(t_list *en, int fd, int flag);
void	new_export(t_mcmd *command, int fd);
void	sel_env(char *s, t_list **en);
int		char_valid(char c);
void	not_many_eq(t_mcmd *command, int i);

int		check_av(char *av);
int		h_check_av(char **str, int k);
int		h_check_av2(char **str, int i);

//	exit
void	my_exit(int flag, int ac, char **av);
void	exit_args(int flag, int ac, char *av[], unsigned int status);
int		is_digit(char *str);

// echo
void	my_echo(char *str[], int fd, int flag);
int		check_option(char *str);
void	without_option(int fd, char *str[], int i, int flag);
void	with_option(int fd, char *str[], int i, int flag);
void	print_echo(char *str, int flag, int fd, int type);

// cd
int		init_cd(t_mcmd *command, int i);
void	my_cd(t_mcmd *command, int i);
char	*cd_arg(t_mcmd *command, int i, char *buf);
void	cd_only(t_mcmd *command, char **buf);
char	*my_getenv(t_list *env, int i);
void	adding_oldpath(t_mcmd *command, char *ori_path);
void	pwd_oldpwd(t_mcmd *command, char *ori_path, char *buf);
void	adding_newpath(t_mcmd *command, char *new_path);

// unset
void	init_unset(t_mcmd *command);
int		check_var(char *str, t_list *en);
t_list	*my_unset(char *str, t_list **en);

// pwd
int		ft_pwd(t_mcmd *command, int fd);

/**************************************************************************
*						*		execution		*
***************************************************************************/

// execute_utils.c
void	is_cmd_path(char **path, char *cmd, char *en[]);
char	*correct_one(char **paths, char *cmd);
char	*make_path(char *cmd, char *en[]);
int		ft_exec(t_mcmd *command);
void	arg_inout(t_mcmd *command, int in, int out);

// execute.c
char	**en_conv(t_list *envp);
void	ft_excusion(char *cmd, t_mcmd *command, char *en[]);
void	exec(t_mcmd *command, char *str, t_list *en);

// main_execute
int		redirect(t_pars *arr, t_mcmd *command);
void	fd_pipe(t_mcmd *command);
void	close_fd(t_mcmd *command);
void	init_exec(t_mcmd *command);
void	exec_action(t_mcmd *command, char **args, int flag);

//	waitpid.c
void	ft_waitpid(t_mcmd *command);
int		status_child(int pid, int index);

/**************************************************************************
* 						*		tools		*
***************************************************************************/

int		check_char(char c1, char c2);
void	ft_free(char **str);
void	free_spl(char **str_spl, int i);
void	free_args_array(t_mcmd *command);
void	exit_error(int code, char *error);
void	free_all(t_mcmd *command);

void	free_two(char **str, int i);
void	sig_handler(int sig);
void	handler(int sig);

int		ft_strcmp(char *s1, char *s2);

int		spaces_check(char *str);
void	ft_print_pars(t_pars *pars);

int		isspaces(char *str);
void	save_home(t_mcmd *command);

/**************************************************************************
* 				*		printing for debuging		*
***************************************************************************/

void	exp_envp(t_list *list, int fd, int flag);
int		is_built(char **str, int i);
int		is_built_child(char **str, int i);
int		is_valid(char *check, char *mesure);
void	args_pars(t_pars pars);

/**************************************************************************
* 					*          parsing			*							  
***************************************************************************/

void	print_struct(t_mcmd *commmad);

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
