/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:29:44 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/25 19:51:49 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* it checks if there is a space between redirection and the infile name	 */
/*****************************************************************************/

void	make_infile(char **sp, t_pars *pars)
{
	if (sp[pars->index][0] == '<' && !sp[pars->index][1])
		open_infile(sp[++pars->index], pars);
	else if (sp[pars->index][0] == '<' && sp[pars->index][1])
		open_infile2(sp[pars->index], pars);
}

/*****************************************************************************/
/* it checks if it's a normal output redirection or it's an append and		 */
/* checks if there is space between redirection and outfile name			 */
/*****************************************************************************/

void	outfile_and_append(char **sp, t_pars *pars)
{
	if (sp[pars->index][0] == '>' && sp[pars->index][1] == '>' &&
		!sp[pars->index][2])
		open_outfile_append(sp[++pars->index], pars);
	else if (sp[pars->index][0] == '>' && sp[pars->index][1] == '>' &&
		sp[pars->index][2])
		open_outfile_append2(sp[pars->index], pars);
	else if (sp[pars->index][0] == '>' && !sp[pars->index][1])
		open_outfile(sp[++pars->index], pars);
	else if (sp[pars->index][0] == '>' && sp[pars->index][1])
		open_outfile2(sp[pars->index], pars);
}

/*****************************************************************************/
/* it opens the infile and return it's file descriptor						 */
/*****************************************************************************/

void	open_infile(char *sp, t_pars *pars)
{
	if (!sp)
		error_exit("syntax error near unexpected token `newline", pars);
	else
	{
		if (*sp == '>' || *sp == '<')
			error_exit("syntax error near unexpected token `newline", pars);
		else
		{
			if (pars->hold_input != STDIN_FILENO)
				close(pars->hold_input);
			pars->hold_input = open(sp, O_RDONLY);
			if (pars->hold_input < 0)
				error_exit("Error in making outfile!", pars);
		}
		pars->index++;
	}
}

/*****************************************************************************/
/* it opens the infile 2 and return it's file descriptor					 */
/*****************************************************************************/

void	open_infile2(char *sp, t_pars *pars)
{
	sp++;
	if (*sp == '>')
		error_exit("syntax error near unexpected token `newline", pars);
	else
	{
		if (pars->hold_input != STDIN_FILENO)
			close(pars->hold_input);
		pars->hold_input = open(sp, O_RDONLY);
		if (pars->hold_input < 0)
			error_exit("Error in making outfile!", pars);
	}
	pars->index++;
}

/*****************************************************************************/
/* it opens the outfile and return it's file descriptor						 */
/*****************************************************************************/

void	open_outfile(char *sp, t_pars *pars)
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
			pars->hold_output = open(sp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (pars->hold_output < 0)
				error_exit("Error in making outfile!", pars);
		}
		pars->index++;
	}
}
