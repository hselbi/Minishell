/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:30:56 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/16 11:50:26 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* error_pipe syntax error unexpected token `|'								 */
/*****************************************************************************/

int	error_pipe(t_pars *pars)
{
	error_exit("syntax error near unexpected token `|'\n", pars);
	return (5);
}

/*****************************************************************************/
/* error_newline syntax error unexpected token `newline'					 */
/*****************************************************************************/

int	error_newline(t_pars *pars)
{
	error_exit("syntax error near unexpected token `newline'\n", pars);
	return (5);
}

/*****************************************************************************/
/* error_pipe syntax error unexpected token `<'								 */
/*****************************************************************************/

int	error_red(t_pars *pars)
{
	error_exit("syntax error near unexpected token `<'\n", pars);
	return (5);
}

/*****************************************************************************/
/* From check_stach_here_doc for norminette									 */
/*****************************************************************************/

int	check_hd(char *line, int i)
{
	t_pars *pars;

	pars = NULL;
	if (!line[i])
		return (error_newline(pars));
	if (line[i] == '<')
		return (error_red(pars));
	else if (line[i] == '|')
		return (error_pipe(pars));
	else if (line[i] == '>')
		return (error_red(pars));
	return (0);
}

/*****************************************************************************/
/* From check_stach_here_doc for norminette									 */
/*****************************************************************************/

int	check_first(char *line, t_pars *pars)
{
	while (line[pars->i] <= 32)
		pars->i++;
	if (line[pars->i] == '|')
		return (error_pipe(pars));
	else if (line[pars->i] == '<' && !line[pars->i +1])
		return (error_red(pars));
	else if (line[pars->i] == '>' && !line[pars->i +1])
		return (error_newline(pars));
	else if (line[pars->i] == '>'
		&& line[pars->i +1] == '>' && !line[pars->i +2])
		return (error_newline(pars));
	else if (line[pars->i] == '<'
		&& line[pars->i +1] == '<' && !line[pars->i +2])
		return (error_newline(pars));
	return (0);
}
