#include "../minishell.h"

/******************************************************
*				*	main of pwd		*
******************************************************/

int	ft_pwd(t_mcmd *command, int fd)
{
	char	buff[1024];
	char	*s1;

	s1 = "PWD";
	getcwd(buff, sizeof(buff));
	if (check_var(s1, command->en) > 0)
		adding_newpath(command, buff);
	if (fd == 1)
	{
		write(command->out, buff, ft_strlen(buff));
		write(command->out, "\n", 1);
	}
	else
		printf("%s\n", buff);
	return (0);
}
