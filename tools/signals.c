#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("\0", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		g_status = 131;
	}
}
