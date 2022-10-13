/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:19:19 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:15:44 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	rest;

	i = 0;
	sign = 1;
	rest = 0;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\n' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rest = rest * 10 + (str[i++] - '0');
		if (rest > LLONG_MAX && sign == 1)
			return (-1);
		if (rest > LLONG_MAX && sign == -1)
			return (0);
	}
	return (rest * sign);
}
