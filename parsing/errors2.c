/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:30:56 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/16 20:38:55 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* error_pipe syntax error unexpected token `|'								 */
/*****************************************************************************/

int	error_pipe()
{
	perror("syntax error near unexpected token `|'\n");
	return (5);
}

/*****************************************************************************/
/* error_newline syntax error unexpected token `newline'					 */
/*****************************************************************************/

int	error_newline()
{
	perror("syntax error near unexpected token `newline'\n");
	return (5);
}

/*****************************************************************************/
/* error_pipe syntax error unexpected token `<'								 */
/*****************************************************************************/

int	error_red()
{
	perror("syntax error near unexpected token `<'\n");
	return (5);
}

/*****************************************************************************/
/* From check_stach_here_doc for norminette									 */
/*****************************************************************************/

int	check_hd(char *line, int i)
{
	if (!line[i])
		return (error_newline());
	if (line[i] == '<')
		return (error_red());
	else if (line[i] == '|')
		return (error_pipe());
	else if (line[i] == '>')
		return (error_red());
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
		return (error_pipe());
	else if (line[pars->i] == '<' && !line[pars->i +1])
		return (error_red());
	else if (line[pars->i] == '>' && !line[pars->i +1])
		return (error_newline());
	else if (line[pars->i] == '>'
		&& line[pars->i +1] == '>' && !line[pars->i +2])
		return (error_newline());
	else if (line[pars->i] == '<'
		&& line[pars->i +1] == '<' && !line[pars->i +2])
		return (error_newline());
	return (0);
}
