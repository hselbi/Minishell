/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:37 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/25 22:53:38 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************************
*				*	main of pwd		*
******************************************************/

int	ft_pwd(t_mcmd *command, int fd)
{
	char	buff[1024];
	char	*s1;

	fd = (int)fd;
	s1 = "PWD";
	getcwd(buff, sizeof(buff));
	if (check_var(s1, command->en))
	{
		adding_newpath(command, buff);
		ft_free(command->av);
	}
	if (fd == 1)
	{
		write(command->out, buff, ft_strlen(buff));
		write(command->out, "\n", 1);
	}
	else
		printf("%s\n", buff);
	return (0);
}
