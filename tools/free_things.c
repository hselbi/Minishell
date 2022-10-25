/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:06:42 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 21:38:22 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_two(char **str, int i)
{
	if (i == 0)
	{
		if (str[0])
		{
			free(str[0]);
			str[0] = NULL;
			free(str[1]);
			str[1] = NULL;
			free(str);
			str = NULL;
		}
	}
	else
	{
		if (str[0])
		{
			free(str[0]);
			free(str[1]);
			free(str);
		}
	}
}

void	free_spl(char **str_spl, int i)
{
	if (i == 1)
	{
		free(str_spl[0]);
		str_spl[0] = NULL;
		free(str_spl);
		str_spl = NULL;
	}
	else if (i > 1)
	{
		free(str_spl[0]);
		str_spl[0] = NULL;
		free(str_spl[1]);
		str_spl[1] = NULL;
		free(str_spl);
		str_spl = NULL;
	}
	else
	{
		free(str_spl[0]);
		str_spl[0] = NULL;
		free(str_spl);
		str_spl = NULL;
	}
}

void	free_args_array(t_mcmd *command)
{
	char	**arr;
	t_pars	*tmp2;
	int		i;

	i = -1;
	while (command->pars.args_array)
	{
		tmp2 = command->pars.args_array->next;
		arr = command->pars.args_array->args;
		i = -1;
		while (arr[++i])
		{
			free (arr[i]);
		}
		free(arr);
		free (command->pars.args_array);
		command->pars.args_array = tmp2;
	}
}
