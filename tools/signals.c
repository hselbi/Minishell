#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		// fprintf(stderr, "\b\b  \b\b");
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status = 1;
	}
	else if (sig == SIGQUIT)
		fprintf(stderr, "\b\b  \b\b");
}


/*

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	void_sig(int sig)
{
	(void)sig;
}

void	void_sig2(int sig)
{
	(void)sig;
	g_exit = 1; // global variable
	fprintf(stderr, "==>\b\b  \b\b");
	rl_replace_line("\n", 0);
	rl_on_new_line();  // back to new line
	rl_redisplay(); //
	rl_catch_signals = 0;
	close(0); // close reading
	printf("exit");
	exit(1);
}

*/
/*need to use them inside pipe and in the main*/

// void	handle_signal(int signum)
// {
// 	if (signum == SIGINT)
// 	{
		// g_var->sig_flag = 1;
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("\0", 0);
// 		rl_redisplay();
// 	}
// 	else if (signum == SIGQUIT)
// 		fprintf(stderr, "\b\b  \b\b");
// 	return ;
// }

// /*	for pipes	*/

// void	handle_signal_pipe(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		close (0);
		// g_var->sig_flag = 1;
// 	}
// 	else if (signum == SIGQUIT)
// 		fprintf(stderr, "\b\b  \b\b");
// 	return ;
// }
// */