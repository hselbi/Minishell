/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:30:56 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/25 21:21:27 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"
#include "../minishell.h"

/*****************************************************************************/
/* error_pipe syntax error unexpected token `|'								 */
/*****************************************************************************/

int	error_pipe(void)
{
	perror("syntax error near unexpected token `|'\n");
	g_status = 258;
	return (5);
}

/*****************************************************************************/
/* error_newline syntax error unexpected token `newline'					 */
/*****************************************************************************/

int	error_newline(void)
{
	perror("syntax error near unexpected token `newline'\n");
	g_status = 258;
	return (5);
}

/*****************************************************************************/
/* error_pipe syntax error unexpected token `<'								 */
/*****************************************************************************/

int	error_red(void)
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
	pars->i = 0;
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
