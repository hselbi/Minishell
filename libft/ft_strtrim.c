/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:51:14 by hselbi            #+#    #+#             */
/*   Updated: 2022/09/24 21:24:38 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_comp(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	char	*rest;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	tab = NULL;
	if (!s1 || !set)
		return (NULL);
	tab = (char *)s1;
	len = ft_strlen((char *)s1);
	while (tab[i] != '\0' && ft_comp(tab[i], (char *)set))
		i++;
	while (len > i && ft_comp(tab[len - 1], (char *)set))
		len--;
	rest = malloc(sizeof(char) * (len - i + 1));
	if (!rest)
		return (NULL);
	while (tab[i] != '\0' && len > i)
		rest[j++] = tab[i++];
	rest[j] = '\0';
	return (rest);
}
