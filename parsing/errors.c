/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:27:10 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/25 23:26:46 by aerrazik         ###   ########.fr       */
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

	i = 0;
	if (line[0] == '|')
		return (error_pipe());
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
		else if (line[i])
			i++;
	}
	if (trigger == 5)
		return (error_pipe());
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
		return (error_newline());
	if (line[pars->i] == '<')
		return (error_red());
	else if (line[pars->i] == '|')
		return (error_pipe());
	else if (line[pars->i] == '>')
		return (error_red());
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
		return (error_newline());
	if (line[pars->i] == '>')
		return (error_newline());
	else if (line[pars->i] == '|')
		return (error_pipe());
	else if (line[pars->i] == '<')
		return (error_newline());
	return (0);
}

/*****************************************************************************/
/* Check_error find out if syntax error										 */
/*****************************************************************************/

int	check_error(char *li, t_pars *pars)
{
	if (check_first(li, pars))
		return (5);
	while (li[pars->i])
	{
		if ((!li[pars->i +1] && li[pars->i] == '>') || (li[pars->i +1]
				&& li[pars->i] == '>' && li[pars->i +1] != '>'))
		{
			if (check_right_red(li, pars))
				return (5);
		}
		else if ((!li[pars->i +1] && li[pars->i] == '<') || (li[pars->i +1]
				&& li[pars->i] == '<' && li[pars->i +1] != '<'))
		{
			if (check_left_red(li, pars))
				return (5);
		}
		else if (li[pars->i +1] && li[pars->i] == '|'
			&& li[pars->i +1] == '|')
		{
			write(2, "Error multiple consecutive pipes !\n", 35);
			return (5);
		}
		pars->i++;
	}
	return (0);
}
