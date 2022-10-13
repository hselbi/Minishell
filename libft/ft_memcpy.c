/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:43 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 12:55:52 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (dst == ((void *)0) && str == ((void *)0))
		return (0);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	return (dest);
}
