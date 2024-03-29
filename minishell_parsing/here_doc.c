/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:33:02 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/13 19:45:55 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

void	child_here_doc(int *fd, t_pars *pars)
{
	char	*line;

	if (!pars->limiter)
		error_exit("syntax error near unexpected token `newline'", pars);
	line = get_next_line(0);
	while (cmp_limiter(pars->limiter, line))
	{
		write(fd[1], line, ft_strleng(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd[0]);
	close(fd[1]);
	free(line);
	free(pars->limiter);
	pars->limiter = NULL;
	exit(0);
}

void	make_input(t_pars *pars)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		error_exit("Pipe problem!", pars);
	pid = fork();
	if (pid == -1)
		error_exit("Fork problem!", pars);
	if (pid == 0)
		child_here_doc(fd, pars);
	close(fd[1]);
	// close(fd[0]);
	pars->hold_input = fd[0];
	pars->nmb_of_hd++;
	waitpid(pid, NULL, 0);
}

/*****************************************************************************/
/* makes the limiter for the here_doc										 */
/*****************************************************************************/

void	limiter_maker(char *commands, t_pars *pars)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * 2);
	if (!new)
		return ;
	new[0] = commands[pars->i];
	new[1] = '\0';
	pars->i++;
	pars->limiter = ft_strjoinn(pars->limiter, new);
}

/*****************************************************************************/
/* skip the << open a pipe to fill it whit all the input recieved till the	 */
/* limiter is found															 */
/*****************************************************************************/

void	for_here_doc(char *cmd, t_pars *pars)
{
	pars->limiter = NULL;
	pars->i += 2;
	pars->check = 0;
	while (cmd[pars->i] <= 32)
		pars->i++;
	if (cmd[pars->i] == '<' || cmd[pars->i] == '>' || cmd[pars->i] == '|')
		error_exit("syntax error near unexpected token", pars);
	while (cmd[pars->i])
	{
		if (pars->check == 0 && (cmd[pars->i] == '<'
				|| cmd[pars->i] == '>' || cmd[pars->i] == ' '))
			break ;
		check_open_quote2(cmd, pars);
		if (cmd[pars->i])
			limiter_maker(cmd, pars);
	}
	printf("limiter is %s\n", pars->limiter);
	if (!pars->limiter)
		error_exit("syntax error near unexpected token `newline'", pars);
	else
		make_input(pars);
}
