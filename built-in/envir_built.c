/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:20 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 01:23:46 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************************
*		* this is one is when in the first time *
******************************************************/

t_list	*ft_env(char **en)
{
	t_list	*tmp_en;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (en[len])
		len++;
	while (i < len)
	{
		if (!i)
			tmp_en = ft_lstnew(en[i]);
		else
			ft_lstadd_back(&tmp_en, ft_lstnew(en[i]));
		i++;
	}
	return (tmp_en);
}
/******************************************************
*	* this only work for if i put export command *
******************************************************/

void	my_env(t_mcmd *command)
{
	if (ft_strlen(command->av[0]) != 3)
	{
		write(2, command->av[0], ft_strlen(command->av[0]));
		write(2, ": Command not found\n", 18);
		g_status = 127;
	}
	else
	{
		write(2, command->av[0], ft_strlen(command->av[0]));
		write(2, ": No such file or directory\n", 28);
		g_status = 1;
	}
}

/******************************************************
*	* this only work for if i put export command *
******************************************************/

void	exp_envp(t_list *list, int fd, int flag)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (!tmp->content)
			tmp = tmp->next;
		if (flag == 1)
		{
			write(fd, tmp->content, ft_strlen(tmp->content));
			write(fd, "\n", 1);
		}
		else
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
