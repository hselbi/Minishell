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
		// printf("&&++> %d\n", g_status);
		waitpid(-1, &stat, 0);
		status_child(stat, i);
	}
	signal(SIGINT, handler);
}

int	status_child(int pid, int index)
{
	int	c_stat;

	c_stat = 0;
	// printf("g_status 0 %d\n", g_status);
	if (WIFEXITED(pid))
	{
		c_stat = WEXITSTATUS(pid);
		// printf("c_stat 1 %d\n", c_stat);
	}
	else if (WIFSIGNALED(pid))
	{
		// fprintf(stderr, "=> %d\n", pid);
		if (pid == 3)
			write(1, "Quit: 3\n", 8);
		// printf("c_stat 2 %d\n", c_stat);
		c_stat = WTERMSIG(pid);
		if (c_stat != 131)
			c_stat += 128;
		// printf("c_stat 3 %d\n", c_stat);
	}
	if (index == 1)
		g_status =  c_stat;
	return (c_stat);
}

/*
void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		kill(0, SIGUSR2);
		kill(0, SIGUSR1);
		write(0, "\n", 1);
	}
	else if (signo == SIGQUIT)
	{
		write(1, "\r", 1);
		kill(0, SIGCONT);
		return ;
	}
	else if (signo == SIGUSR1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	else if (signo == SIGUSR2)
	{
		g_exit_status_code = 1;
	}
}
void	signal_fatal_error(int signo)
{
	if (signo == SIGUSR1)
	{
		kill(0, SIGUSR2);
	}
	else if (signo == SIGUSR2)
	{
		g_exit_status_code = 130;
	}
}
*/