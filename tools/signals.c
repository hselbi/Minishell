#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status = 1;
	}
	else if (sig == SIGQUIT)
		fprintf(stderr, "\b\b  \b\b");
}
