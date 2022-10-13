/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:49:18 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:18:03 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if ((*lst) == NULL)
	{
		(*lst) = new;
		(*lst)->next = NULL;
	}
	else
	{
		new->next = (*lst);
		(*lst) = new;
	}
}
