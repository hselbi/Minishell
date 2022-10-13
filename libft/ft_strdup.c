/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:09:49 by hselbi            #+#    #+#             */
/*   Updated: 2022/09/24 21:24:02 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	size_t	l;
	char	*tab;

	i = 0;
	if (!s1)
		return (NULL);
	l = ft_strlen(s1);
	tab = (char *)malloc(sizeof(char) * (l + 1));
	if (!tab)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
