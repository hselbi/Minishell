/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:38:06 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/16 15:44:09 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* it makes the linked list of structs to execute							 */
/*****************************************************************************/

void	make_struct_to_execute(t_pars *pars)
{
	char	**sp;
	int		j;
	int		cmd_nmb;
	char	**args;
	t_pars	*crea_node;

	pars->error = 0;
	if (!pars->for_struct)
		return ;
	sp = ft_spliti(pars->for_struct, '	');
	free(pars->for_struct);
	cmd_nmb = count_commands(sp);
	args = (char **)malloc(sizeof(char *) * (cmd_nmb + 1));
	if (!args)
		return ;
	pars->index = 0;
	j = 0;
	while (sp[pars->index])
	{
		if (pars->error)
			break ;
		if (sp[pars->index][0] == '>')
			outfile_and_append(sp, pars);
		else if (sp[pars->index][0] == '<')
			make_infile(sp, pars);
		else
			args[j++] = sp[pars->index++];
	}
	args[j] = NULL;
	crea_node = new_lst(args, pars);
	back_lstadd(&pars->args_array, crea_node);
	free(crea_node);
	free(sp);
}
