/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:38:06 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/22 22:14:00 by hselbi           ###   ########.fr       */
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
	// fprintf(stderr, "1/ %s\n2/ %s\n", mst.sp[0], mst.sp[1]);÷
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
	int i = -1;
	while (mst.sp[++i])
		free (mst.sp[i]);
	free(mst.sp);
	back_lstadd(&pars->args_array, new_lst(mst.args, pars));
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
