#include "../minishell.h"

void	ft_waitpid(t_mcmd *command)
{
	int	stat;
	int	i;

	stat = 0;
	i = 0;
	while (++i < command->ac)
	{
		waitpid(-1, &stat, 0);
		status_child(stat);
	}
}

int	status_child(int pid)
{
	if (WIFEXITED(pid))
		g_status = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		g_status = WTERMSIG(pid);
		if (g_status != 131)
			g_status += 128;
	}
	return (g_status);
}
