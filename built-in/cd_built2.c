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
