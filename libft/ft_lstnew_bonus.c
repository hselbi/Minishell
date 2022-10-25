/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:49:41 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/22 22:32:16 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nwnode;

	nwnode = malloc(sizeof(t_list));
	if (!nwnode)
		return (NULL);
	nwnode->content = ft_strdup(content);
	nwnode->next = NULL;
	return (nwnode);
}
