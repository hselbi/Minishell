/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:06:56 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 13:27:31 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*str;
	size_t	i;

	i = 0;
	dest = (char *) dst;
	str = (char *) src;
	i = 0;
	if (str > dest)
	{
		while (len > i)
		{
			dest[i] = str[i];
			i++;
		}
	}
	else if (str < dest)
	{
		while (len > 0)
		{
			dest[len - 1] = str[len - 1];
			len--;
		}
	}
	return (dest);
}
