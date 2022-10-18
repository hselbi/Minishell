/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:07:20 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/18 19:28:54 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* check_open_quote as it name says it checks if quotes are open or not		 */
/*****************************************************************************/

void	check_open_quote(char *sp, t_pars *pars)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		if (sp[i] == '"' && pars->check == 0)
			pars->check = D_COTE;
		else if (sp[i] == '\'' && pars->check == 0)
			pars->check = COTE;
		else if (sp[i] == '"' && pars->check == D_COTE)
			pars->check = 0;
		else if (sp[i] == '\'' && pars->check == COTE)
			pars->check = 0;
		i++;
	}
}

/*****************************************************************************/
/* It counts the number of commands											 */
/*****************************************************************************/

int	count_commands(char **sp)
{
	int	i;

	i = 0;
	if (!sp)
		return (0);
	while (sp[i])
		i++;
	return (i);
}

/*****************************************************************************/
/* befor_make_struct split the whole line with pipes and send them to		 */
/* make_struct to make them ready to execute								 */
/*****************************************************************************/

void	befor_make_struct(char *line, t_pars *pars)
{
	t_bfs	bfs;
	
	bfs.sp = ft_split_with_pipe(line, '|', pars);
	bfs.i = 0;
	bfs.cont = bfs.sp[bfs.i];
	pars->trigger = 0;
	pars->check = 0;
	while (bfs.sp[bfs.i])
	{
		check_open_quote(bfs.sp[bfs.i], pars);
		while (pars->check != 0)
		{
			if (!bfs.sp[bfs.i +1])
			{
				free_cont(bfs.cont, pars);
				break ;
			}
			check_open_quote(bfs.sp[bfs.i +1], pars);
			bfs.cont = ft_strjoin_pipe(bfs.cont, bfs.sp[++bfs.i]);
		}
		if (pars->trigger)
			break ;
		make_struct(bfs.cont, pars);

		if (pars->check == 0)
			bfs.cont = bfs.sp[bfs.i +1];
		bfs.i++;
	}
	free(bfs.sp);
}

void	free_cont(char *cont, t_pars *pars)
{
	error_exit("syntax error near unexpected token ' or \" ", pars);
	pars->trigger = 9;
	if (cont)
		free(cont);
}
