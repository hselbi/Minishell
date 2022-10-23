#include "../minishell.h"

void	exit_error(int code, char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(code);
}
