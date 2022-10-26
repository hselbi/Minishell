/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:23 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 00:15:45 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************************
*			*  a string has a digit  *
******************************************************/

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/******************************************************
*			*  process exit with args  *
******************************************************/
void	exit_args(int flag, int ac, char *av[], unsigned int status)
{
	if (ac == 3 && is_digit(av[1]))
	{
		status = (unsigned int)ft_atoi(av[1]) % 256;
		exit(status);
	}
	else if (!is_digit(av[1]))
	{
		if (flag == 2)
			puts("exit");
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (ac > 3)
	{
		if (flag == 2)
			puts("exit");
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_status = 1;
	}
}

/******************************************************
*			*	main of exit	*
******************************************************/

void	my_exit(int flag, int ac, char **av)
{
	unsigned int	status;

	status = 0;
	if (ac == 2)
	{
		if (flag == 2)
			puts("exit");
		exit(EXIT_SUCCESS);
	}
	else if (ac >= 3)
		exit_args(flag, ac, av, status);
}
