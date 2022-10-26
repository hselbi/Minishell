/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:54:29 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 01:34:58 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************************************************
*	 	* 			check a between two characters				*
************************************************************************/

int	check_char(char c1, char c2)
{
	return (c1 - c2);
}

/************************************************************************
*	 * 			check a white-spaces in a string				*
************************************************************************/

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (!(*s1) || !(*s2))
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/************************************************************************
*	 * 			check a white-spaces in a string				*
************************************************************************/

int	isspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 32)
			return (0);
		i++;
	}
	return (1);
}

/************************************************************************
*	  * 				check a spaces in a string					*
************************************************************************/

int	spaces_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

/************************************************************************
*		 		*			path home back-up			*
************************************************************************/
void	save_home(t_mcmd *command)
{
	int		i;
	t_list	*arr;

	i = 0;
	arr = command->en;
	if (check_var("HOME", arr))
	{
		while (arr->content != NULL
			&& ft_strncmp("HOME=", arr->content, 5) != 0)
			arr = arr->next;
		command->home = ft_strdup(arr->content);
	}
}
