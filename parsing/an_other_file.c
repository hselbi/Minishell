/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_other_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:25:53 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 23:32:49 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* It expands an alphanumeric expandable thing                               */
/*****************************************************************************/

void	normal_expand(t_dlr *dlr, t_pars *pars, char *word)
{
	while (!ft_isalnum_dyali(word[dlr->i]) && word[dlr->i])
		dlr->i++;
	dlr->dlr_exp = expand_it(make_word(word, dlr->begin, dlr->i - 1), pars, 1);
	dlr->expd = ft_strjoinn(dlr->expd, dlr->dlr_exp);
}

/*****************************************************************************/
/* It expands an $?                                                          */
/*****************************************************************************/

void	check_exit(t_dlr *dlr, t_pars *pars)
{
	dlr->expd = ft_strjoinn(dlr->expd, expand_it("?\0", pars, 1));
	dlr->i++;
}

/*****************************************************************************/
/* It joins befor and after what to expand                                   */
/*****************************************************************************/

void	join_to_expanded(t_dlr *dlr, char *word)
{
	dlr->begin = dlr->i;
	if (word[dlr->i - 1] == '$')
		dlr->begin = dlr->i - 1;
	while (word[dlr->i] && word[dlr->i] != '$')
		dlr->i++;
	dlr->expd = ft_strjoinn(dlr->expd, make_word(word, dlr->begin, dlr->i - 1));
}
