/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:50 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 13:58:14 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpid(t_mcmd *command)
{
	int	stat;
	int	i;

	stat = 0;
	signal(SIGINT, SIG_IGN);
	i = 0;
	while (++i < command->ac)
	{
		waitpid(-1, &stat, 0);
		status_child(stat, i);
	}
	signal(SIGINT, handler);
}

int	status_child(int pid, int index)
{
	int	c_stat;

	c_stat = 0;
	if (WIFEXITED(pid))
	{
		c_stat = WEXITSTATUS(pid);
	}
	else if (WIFSIGNALED(pid))
	{
		if (pid == 3)
			write(1, "Quit: 3\n", 8);
		c_stat = WTERMSIG(pid);
		if (c_stat != 131)
			c_stat += 128;
	}
	if (index == 1 && !g_status)
		g_status =  c_stat;
	return (c_stat);
}
