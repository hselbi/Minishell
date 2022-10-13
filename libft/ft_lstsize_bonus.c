/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:50:19 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:18:39 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*nwnode;

	count = 0;
	nwnode = lst;
	while (nwnode != NULL)
	{
			count++;
			nwnode = nwnode->next;
	}
	return (count);
}
