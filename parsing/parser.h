/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:30:26 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/16 12:05:14 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include<stdlib.h>
# include<stdio.h>
# include<unistd.h>
# include <errno.h>
# include<fcntl.h>
# include<sys/wait.h>
# include"get_next_line.h"
# include<readline/readline.h>
# include<readline/history.h>
# include "../libft/libft.h"

typedef struct s_plit
{
	char	**spl;
	int		i;
	int		j;
	int		b;
}	t_sp;

enum
{
	ZERO,
	D_COTE,
	COTE,
	HERE_DOC,
	INFILE,
	APPEND,
	OUTFILE
};

typedef struct s_pars
{
	int				i;
	int				check;
	int				nodes_nmb;
	int				index;
	int				trigger;
	int				exp;
	char			*for_struct;
	char			*file;
	char			*limiter;
	char			*command;
	char			*here_doc_limiter;
	char			*infile;
	char			*outfile;
	t_list			*env;
	int				hold_input;
	int				hold_output;
	struct s_pars	*args_array;
	char			**args;
	int				fd_input;
	int				fd_output;
	int				error;
	int				nmb_of_hd;
	struct s_pars	*next;
}	t_pars;

/*****************************************************************************/
/*	Functions for expanding													 */
/*****************************************************************************/

char	*expand_it(char	*to_expand, t_pars *pars, int trig);
char	*take_what_to_expand(char *sentance, t_pars *pars);
char	*check_dollar(char *word, t_pars *pars);
void	check_valid_dollar(char *cmd, t_pars *pars);

/*****************************************************************************/
/*	Functions for redirections												 */
/*****************************************************************************/

void	open_outfile(char *sp, t_pars *pars);
void	open_outfile2(char *sp, t_pars *pars);
void	open_outfile_append(char *sp, t_pars *pars);
void	open_outfile_append2(char *sp, t_pars *pars);
void	outfile_and_append(char **sp, t_pars *pars);
void	open_infile(char *sp, t_pars *pars);
void	open_infile2(char *sp, t_pars *pars);
void	make_infile(char **sp, t_pars *pars);

/*****************************************************************************/
/*	Functions for quotes and double quotes									 */
/*****************************************************************************/

void	take_word(char *commands, t_pars *pars, int i);
void	take_word_2(char *commands, t_pars *pars, int i);
void	check_open_quote2(char *sp, t_pars *pars);

void	make_struct_to_execute(t_pars *pars);
void	split_with_pipe(char *line);
char	*content(char *line, int len, int i);
void	make_struct(char *commands, t_pars *pars);
void	for_here_doc(char *cmd, t_pars *pars);
void	child_here_doc(int *fd, t_pars *pars);
void	make_input(t_pars *pars);
void	befor_make_struct(char *line, t_pars *pars);

/*****************************************************************************/
/*	Functions for errors handling											 */
/*****************************************************************************/

void	error_exit(char *str, t_pars *pars);
int		check_pipe_error(char *line);
int		error_pipe(t_pars *pars);
int		error_newline(t_pars *pars);
int		error_red(t_pars *pars);

/* Outils functions */
char	*space(char *str);
char	**ft_spliti(char *s, char c);
size_t	ft_strleng(char *str);
char	*ft_strdupl(char *s1);
int		cmp_limiter(char *str1, char *str2);
int		ft_isalnumb(char str);
int		ft_isalnum_dyali(char str);
char	*ft_strjoinn(char *s1, char *s2);
char	*ft_iitoa(int n);
char	*make_word(char *sentance, int begin, int end);
int		cmp(char *str1, char *str2);
t_pars	*new_lst(char **args, t_pars *pars);
void	back_lstadd(t_pars **alst, t_pars *new);
t_pars	*last_lst(t_pars *lst);
char	**ft_split_with_pipe(char *s, char c, t_pars *pars);
char	*ft_strjoin_pipe(char *s1, char *s2);
char	*ft_strjoin_space(char *s1, char *s2);
int		count_commands(char **sp);
char	*split_it(char *cont);
int		check_error(char *line, t_pars *pars);
int		check_left_red(char *line, t_pars *pars);
int		check_right_red(char *line, t_pars *pars);
int		check_stach_here_doc(char *line);
int		check_hd(char *line, int i);
int		check_first(char *line, t_pars *pars);
char	*ft_strdupp(char *s1);

/*********************/

#endif
