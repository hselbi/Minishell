/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:38:06 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 22:27:36 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* it makes the linked list of structs to execute							 */
/*****************************************************************************/

void	make_struct_to_execute(t_pars *pars)
{
	t_mst	mst;

	if (!pars->for_struct)
		return ;
	mst.sp = ft_spliti(pars->for_struct, '	');
	free(pars->for_struct);
	mst.cmd_nmb = count_commands(mst.sp);
	mst.args = (char **)malloc(sizeof(char *) * (mst.cmd_nmb + 1));
	if (!mst.args)
		return ;
	mst.j = 0;
	while (mst.sp[pars->index])
	{
		if (pars->error)
			break ;
		if (mst.sp[pars->index][0] == '>')
			outfile_and_append(mst.sp, pars);
		else if (mst.sp[pars->index][0] == '<')
			make_infile(mst.sp, pars);
		else
			mst.args[mst.j++] = ft_strdupl(mst.sp[pars->index++]);
	}
	mst.args[mst.j] = NULL;
	free_sp(mst.sp);
	back_lstadd(&pars->args_array, new_lst(mst.args, pars));
}

void	free_sp(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		free (sp[i]);
	free(sp);
}

int	check_check(char *line, t_pars *pars)
{
	int	syntax_error;

	syntax_error = check_error(line, pars);
	pars->i = 0;
	if (syntax_error)
	{
		while (line[pars->i])
		{
			if (line[pars->i] == '<' && line[pars->i + 1] == '<')
			{
				while (line[pars->i] <= 32)
					pars->i++;
				if (line[pars->i] == '<' || line[pars->i] == '>'
					|| line[pars->i] == '|')
					break ;
				for_here_doc(line, pars);
				close(pars->hold_input);
			}
			else
				pars->i++;
		}
		return (5);
	}
	return (0);
}
