/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 08:22:58 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 23:36:34 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"
#include"../minishell.h"

char	*split_it(char *cont)
{
	int		i;
	char	**sp;
	char	*cont_rep;

	i = 0;
	while (cont[i])
	{
		if (cont[i] >= 9 && cont[i] <= 13)
			cont[i] = ' ';
		i++;
	}
	sp = ft_spliti(cont, ' ');
	free(cont);
	i = 0;
	cont_rep = NULL;
	while (sp[i])
	{
		cont_rep = ft_strjoin_space(cont_rep, sp[i]);
		i++;
	}
	free(sp);
	return (cont_rep);
}

/*****************************************************************************/
/* expand_it it expand the argument after dollar sign if it's available in   */
/* env 																		 */
/*****************************************************************************/

char	*expand_it(char	*to_expand, t_pars *pars, int trig)
{
	int		begin;
	int		end;
	char	*cont;

	if (!to_expand)
		return (NULL);
	if (!cmp(to_expand, "?"))
		return (ft_iitoa(g_status));
	while (pars->env)
	{
		cont = pars->env->content;
		if (!cmp(cont, to_expand) && cont[ft_strleng(to_expand)] == '=')
		{
			begin = ft_strleng(to_expand) + 1;
			end = ft_strleng(cont) - 1;
			free(to_expand);
			if (trig == 0)
				return (split_it(make_word(cont, begin, end)));
			return (make_word(cont, begin, end));
		}
		pars->env = pars->env->next;
	}
	free(to_expand);
	return (NULL);
}

/*****************************************************************************/
/* take_what_to_expand delimited by white spaces return the argument to 	 */
/* expand 																	 */
/*****************************************************************************/

char	*take_what_to_expand(char *sentance, t_pars *pars)
{
	int	begin;

	pars->i++;
	begin = pars->i;
	if (!sentance)
		return (NULL);
	if (ft_isalnum_dyali(sentance[pars->i]) == 1)
		return (NULL);
	while (!ft_isalnum_dyali(sentance[pars->i]) && sentance[pars->i])
				pars->i++;
	return (make_word(sentance, begin, pars->i - 1));
}

/*****************************************************************************/
/* check_dollar it checks dollar in double quotes and expand it				 */
/*****************************************************************************/

char	*check_dollar(char *word, t_pars *pars)
{
	t_dlr	dlr;

	dlr.i = 0;
	dlr.expd = NULL;
	while (word[dlr.i])
	{
		if (word[dlr.i] == '$')
		{
			dlr.begin = ++dlr.i;
			if (word[dlr.begin] == '?')
				check_exit(&dlr, pars);
			else
				normal_expand(&dlr, pars, word);
		}
		else
			join_to_expanded(&dlr, word);
	}
	free(word);
	return (dlr.expd);
}

/*****************************************************************************/
/* check_valid_dollar skip the dollar sign if there is nothing to expand and */
/* and expand it if the opposite											 */
/*****************************************************************************/

void	check_valid_dollar(char *cmd, t_pars *pars)
{
	char	*str;

	if (cmd[pars->i + 1] == '?')
	{
		pars->i++;
		str = expand_it("?\0", pars, 1);
		pars->for_struct = ft_strjoinn(pars->for_struct, str);
		pars->i++;
	}
	else if (ft_isalnum_dyali(cmd[pars->i + 1]))
		pars->i++;
	else
	{
		str = expand_it(take_what_to_expand(cmd, pars), pars, 0);
		pars->for_struct = ft_strjoinn(pars->for_struct, str);
	}
}
