/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:37:29 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/19 18:04:35 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

t_pars	*new_lst(char **args, t_pars *pars)
{
	t_pars	*head;

	head = (struct s_pars *)malloc(sizeof(struct s_pars));
	if (!head)
		return (0);
	head->args = args;
	head->fd_input = pars->hold_input;
	head->fd_output = pars->hold_output;
	head->next = NULL;
	return (head);
}

t_pars	*last_lst(t_pars *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	back_lstadd(t_pars **alst, t_pars *new)
{
	if (!new)
		return ;
	if (! *alst)
	{
		*alst = new;
		// free÷(new);
		return ;
	}
	last_lst(*alst)->next = new;
	// free(new);
}

int	cmp_limiter(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (1);
	if (ft_strleng(str1) != ft_strleng(str2))
		return (1);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
	}
	return (0);
}

int	cmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (1);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
	}
	return (0);
}
