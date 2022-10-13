/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:10:03 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:03:38 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	j;
	size_t			i;
	unsigned char	*a;

	j = (unsigned char) c;
	i = 0;
	a = (unsigned char *) b;
	while (len > i)
	{
		a[i] = j;
		i++;
	}
	return (a);
}
