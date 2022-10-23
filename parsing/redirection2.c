/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:29:57 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/23 15:24:54 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* it opens the outfile2 and return it's file descriptor					 */
/*****************************************************************************/

void	open_outfile2(char *sp, t_pars *pars)
{
	sp++;
	if (*sp == '<')
		error_exit("syntax error near unexpected token `<'", pars);
	else
	{
		if (pars->hold_output != STDOUT_FILENO)
			close(pars->hold_output);
		pars->hold_output = open(sp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pars->hold_output < 0)
			error_exit("Error in making outfile!", pars);
	}
	pars->index++;
}

/*****************************************************************************/
/* it opens the outfile appends and return it's file descriptor				 */
/*****************************************************************************/

void	open_outfile_append(char *sp, t_pars *pars)
{
	if (!sp)
		error_exit("syntax error near unexpected token `newline", pars);
	else
	{
		if (*sp == '>')
			error_exit("syntax error near unexpected token `>'", pars);
		else if (*sp == '<')
			error_exit("syntax error near unexpected token `<'", pars);
		else
		{
			if (pars->hold_output != STDOUT_FILENO)
				close(pars->hold_output);
			pars->hold_output = open(sp, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pars->hold_output < 0)
				error_exit("Error in making outfile!", pars);
		}
		pars->index++;
	}
}

/*****************************************************************************/
/* it opens the outfile appends 2 and return it's file descriptor			 */
/*****************************************************************************/

void	open_outfile_append2(char *sp, t_pars *pars)
{
	sp++;
	sp++;
	printf("----%s---\n", sp);
	if (*sp == '>')
		error_exit("syntax error near unexpected token `>'", pars);
	else if (*sp == '<')
		error_exit("syntax error near unexpected token `<'", pars);
	else
	{
		if (pars->hold_output != STDOUT_FILENO)
			close(pars->hold_output);
		pars->hold_output = open(sp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pars->hold_output < 0)
			error_exit("Error in making outfile!", pars);
	}
	pars->index++;
}
