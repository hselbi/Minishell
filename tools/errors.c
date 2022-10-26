/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:54:18 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 19:28:04 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(int code, char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(code);
}

int	is_built_child(char **str, int i)
{
	i = 0;
	while (str[i])
		i++;
	if (!ft_strcmp(str[0], "export"))
		return (0);
	else if (i == 1 && !ft_strcmp(str[0], "env"))
		return (0);
	else if (!ft_strcmp(str[0], "exit"))
		return (0);
	else if (!ft_strcmp(str[0], "unset"))
		return (0);
	else if (!ft_strcmp(str[0], "cd"))
		return (0);
	else if (!ft_strcmp(str[0], "pwd"))
		return (0);
	else if (!ft_strcmp(str[0], "echo"))
		return (0);
	return (1);
}