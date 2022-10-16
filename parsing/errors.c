/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:27:10 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/16 11:50:07 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* check_pipe_error if pipe at first or last								 */
/*****************************************************************************/

int	check_pipe_error(char *line)
{
	int	i;
	int	trigger;
	t_pars	*pars;

	i = 0;
	pars = NULL;
	if (line[0] == '|')
		return (error_pipe(pars));
	trigger = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			trigger = 5;
			i++;
		}
		else if (trigger == 5 && !((line[i] && line[i] >= 9
					&& line[i] <= 13) || line[i] == ' '))
			trigger = 0;
		if (line[i])
			i++;
	}
	if (trigger == 5)
		return (error_pipe(pars));
	return (0);
}

/*****************************************************************************/
/* It checks if there is more than 16 here_doc to execute and exit minishell */
/*****************************************************************************/

int	check_stach_here_doc(char *line)
{
	int	i;
	int	nmb_of_hd;

	i = 0;
	nmb_of_hd = 0;
	while (line[i])
	{
		if (line[i +1] && line[i] == '<' && line[i +1] == '<')
		{
			i += 2;
			while (line[i] && line[i] <= 32)
				i++;
			if (check_hd(line, i))
				return (check_hd(line, i));
			else
				nmb_of_hd++;
		}
		i++;
	}
	if (nmb_of_hd > 16)
	{
		write(2, "maximum here-document count exceeded\n", 37);
		exit(2);
	}
	return (0);
}

/*****************************************************************************/
/* From check_error for norminette											 */
/*****************************************************************************/

int	check_right_red(char *line, t_pars *pars)
{
	pars->i++;
	while (line[pars->i] && line[pars->i] <= 32)
		pars->i++;
	if (!line[pars->i])
		return (error_newline(pars));
	if (line[pars->i] == '<')
		return (error_red(pars));
	else if (line[pars->i] == '|')
		return (error_pipe(pars));
	else if (line[pars->i] == '>')
		return (error_red(pars));
	return (0);
}

/*****************************************************************************/
/* From check_error for norminette											 */
/*****************************************************************************/

int	check_left_red(char *line, t_pars *pars)
{
	pars->i++;
	while (line[pars->i] && line[pars->i] <= 32)
		pars->i++;
	if (!line[pars->i])
		return (error_newline(pars));
	if (line[pars->i] == '>')
		return (error_newline(pars));
	else if (line[pars->i] == '|')
		return (error_pipe(pars));
	else if (line[pars->i] == '<')
		return (error_newline(pars));
	return (0);
}

/*****************************************************************************/
/* Check_error find out if syntax error										 */
/*****************************************************************************/

int	check_error(char *line, t_pars *pars)
{
	pars->i = 0;
	if (check_first(line, pars))
		return (5);
	while (line[pars->i])
	{
		if (line[pars->i +1] && line[pars->i] == '>' && line[pars->i +1] != '>')
		{
			if (check_right_red(line, pars))
				return (5);
		}
		else if (line[pars->i +1] && line[pars->i] == '<'
			&& line[pars->i +1] != '<')
		{
			if (check_left_red(line, pars))
				return (5);
		}
		else if (line[pars->i +1] && line[pars->i] == '|'
			&& line[pars->i +1] == '|')
		{
			write(2, "Error multiple consecutive pipes !\n", 35);
			return (5);
		}
		pars->i++;
	}
	return (0);
}
