/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:23:27 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:37:51 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*my_strcat(char *dest, char *s1, char *s2, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (size > j)
	{
		while (s1[i])
			dest[j++] = s1[i++];
		i = 0;
		while (s2[i])
			dest[j++] = s2[i++];
		dest[j] = '\0';
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		sl1;
	int		sl2;
	int		total;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup(""));
	sl1 = ft_strlen((char *)s1);
	sl2 = ft_strlen((char *)s2);
	total = sl1 + sl2;
	str = (char *)malloc(sizeof(char) *(total + 1));
	if (!str)
		return (NULL);
	my_strcat(str, (char *)s1, (char *)s2, total);
	return (str);
}
