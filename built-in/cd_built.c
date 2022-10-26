/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:12 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 02:14:21 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************************
*  		*  print error if it's not there  *
******************************************************/

char	*cd_arg(t_mcmd *command, int i, char *buf)
{
	if (!ft_strcmp(command->av[i + 1], "."))
	{
		buf = getcwd(NULL, 0);
		if (!buf)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
			ft_putstr_fd("cannot access parent directories: No such file ", 2);
			ft_putstr_fd("or directory\n", 2);
		}
		return (buf);
	}
	else
	{
		if (chdir(command->av[i + 1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(command->av[i + 1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		buf = getcwd(NULL, 0);
		return (buf);
	}
}

/******************************************************
*  				*	get from my env		*
******************************************************/

char	*my_getenv(t_list *env, int i)
{
	char	*str;
	t_list	*tmp;
	char	**spl;

	tmp = env;
	while (i-- > 1)
		tmp = tmp->next;
	spl = ft_split(tmp->content, '=');
	if (!spl[1])
	{
		str = ft_strdup(".");
		free_two(spl, 1);
	}
	else
	{
		str = ft_strdup(tmp->content + 5);
		free_two(spl, 1);
	}
	return (str);
}

/******************************************************
*  			*	only cd without args	 *
******************************************************/

void	cd_only(t_mcmd *command, char **buf)
{
	int	i;

	i = check_var("HOME", command->en);
	if (i > 0)
		*buf = my_getenv(command->en, i);
	else
		*buf = NULL;
	if (chdir(*buf) == -1)
	{
		g_status = 1;
		ft_putstr_fd("cd: HOME not set\n", 2);
	}
}

/******************************************************
*  			*	process of cd function	 *
******************************************************/

void	my_cd(t_mcmd *command, int ac)
{
	char	buffer[1024];
	char	*buf;
	char	*ori_path;

	getcwd(buffer, sizeof(buffer));
	buf = buffer;
	ori_path = ft_strdup(buffer);
	if (ac >= 3)
		buf = cd_arg(command, 0, buf);
	else if (ac == 2)
		cd_only(command, &buf);
	if (check_var("PWD", command->en))
	{
		adding_oldpath(command, ori_path);
		ft_free(command->av);
		adding_newpath(command, buf);
		ft_free(command->av);
	}
	else
	{
		adding_newpath(command, buf);
		ft_free(command->av);
	}
	if (buf)
		free(buf);
	free(ori_path);
}

/******************************************************
*  				*  main cd function  *
******************************************************/

int	init_cd(t_mcmd *command, int i)
{
	int	ac;

	i = 0;
	ac = 1;
	while (command->av[i])
	{
		ac++;
		i++;
	}
	my_cd(command, ac);
	return (1);
}
