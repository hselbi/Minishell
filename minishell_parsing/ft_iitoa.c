/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:27:27 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/11 22:23:01 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	len(int n)
{
	unsigned int	i;
	int				j;

	i = n;
	j = 0;
	if (n < 0)
	{
		i = n * -1;
		j = 1;
	}
	if (i == 0)
		j++;
	while (i > 0)
	{
		i = i / 10;
		j++;
	}
	return (j);
}

char	*ft_iitoa(int n)
{
	char			*str;
	int				i;
	unsigned int	j;

	j = n;
	i = len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	i--;
	if (n < 0)
		j = n * -1;
	while (i >= 0)
	{
		if (i == 0 && n < 0)
		{
			str[i] = '-';
			break ;
		}
		str[i] = '0' + j % 10;
		j = j / 10;
		i--;
	}
	return (str);
}
