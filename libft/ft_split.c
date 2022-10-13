/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:01:43 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:15:29 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	matchin(char tfind, char std)
{
	if (tfind == std)
		return (1);
	return (0);
}

static int	sizewrd(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && matchin(str[i], c))
		i++;
	while (str[i] && !matchin(str[i], c))
	{
		i++;
		j++;
	}
	return (j);
}

static int	wrd(char *str, char ch)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i])
	{
		while (str[i] && matchin(str[i], ch))
			i++;
		if (str[i] && !matchin(str[i], ch))
		{
			r++;
			while (str[i] && !matchin(str[i], ch))
				i++;
		}
	}
	return (r);
}

static char	**process(char **tabl, int wrdlen, char *str, char ch)
{
	int	k;
	int	j;

	k = -1;
	while (++k < wrdlen)
	{
		tabl[k] = malloc(sizeof(char) * (sizewrd(str, ch) + 1));
		if (!tabl)
			return (NULL);
		j = 0;
		while (matchin(*str, ch))
			str++;
		while (*str && !(matchin(*str, ch)))
			tabl[k][j++] = *str++;
		tabl[k][j] = '\0';
	}
	tabl[k] = NULL;
	return (tabl);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		lwrd;

	if (!s)
		return (NULL);
	lwrd = wrd((char *)s, c);
	tab = (char **)malloc(sizeof(char *) * (lwrd + 1));
	if (!tab)
		return (NULL);
	process(tab, lwrd, (char *)s, c);
	return (tab);
	free(tab);
}
