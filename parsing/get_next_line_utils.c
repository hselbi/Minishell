/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:25:00 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 22:20:20 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"
#include"get_next_line.h"

char	*ft_strjoinnn(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (ft_strleng(s1) + ft_strleng(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

int	ft_strchrr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != (char)c)
			s++;
		else
			return (1);
	}
	if (*s == (char)c)
		return (1);
	return (0);
}

char	*ft_strdupl(char *s1)
{
	char	*s2;
	int		i;

	if (!s1)
		return (0);
	s2 = malloc(sizeof(char) * ft_strleng(s1) + 2);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
		s2[i++] = '\n';
	s2[i] = '\0';
	return (s2);
}

char	*ft_strdupp(char *s1)
{
	char	*s2;
	int		i;

	if (!s1)
		return (0);
	s2 = malloc(sizeof(char) * ft_strleng(s1) + 2);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		s2[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
		s2[i++] = '\n';
	s2[i] = '\0';
	return (s2);
}
