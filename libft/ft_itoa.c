/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:43:02 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 16:18:21 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenint(long long n)
{
	int	l;

	l = 1;
	while (n >= 10)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static char	*ctos(long long a, int s)
{
	int		l;
	char	*set;

	l = lenint(a) + s;
	set = malloc(sizeof(char) * (l + 1));
	if (!set)
		return (NULL);
	set[l--] = '\0';
	while (l >= 0)
	{
		set[l] = (a % 10) + '0';
		a = a / 10;
		if (s == 1 && l == 0)
			set[0] = '-';
		l--;
	}
	return (set);
}

char	*ft_itoa(int n)
{
	long long	nb;
	int			sign;

	nb = n;
	sign = 0;
	if (n < 0)
	{
		nb = -nb;
		sign = 1;
	}
	return (ctos(nb, sign));
}
