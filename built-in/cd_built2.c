/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:15 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 10:42:20 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************************
*  			*  adding new path in PWD  *
******************************************************/

void	adding_newpath(t_mcmd *command, char *new_path)
{
	command->av = (char **)malloc(sizeof(char *) * 3);
	command->av[0] = ft_strdup("export");
	command->av[1] = ft_strjoin("PWD=", new_path);
	command->av[2] = NULL;
	new_export(command, 1);
}

/******************************************************
*  		*  adding previous path in OLDPWD  *
******************************************************/

void	adding_oldpath(t_mcmd *command, char *ori_path)
{
	command->av = (char **)malloc(sizeof(char *) * 3);
	command->av[0] = ft_strdup("export");
	command->av[1] = ft_strjoin("OLDPWD=", ori_path);
	command->av[2] = NULL;
	new_export(command, 1);
}

/******************************************************
**  making new pwd and oldpwd if there's already pwd  *
******************************************************/

void	pwd_oldpwd(t_mcmd *command, char *ori_path, char *buf)
{
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
}