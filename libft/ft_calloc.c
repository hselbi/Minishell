/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:50:47 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:10:00 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*pnt;

	pnt = (void *)malloc(count * size);
	if (!pnt)
	{
		return (NULL);
		errno = ENOMEM;
	}	
	if (pnt)
		ft_bzero(pnt, size * count);
	return (pnt);
}
