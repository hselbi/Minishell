#include "../minishell.h"

/******************************************************
*  		*  compare lowercase with uppercase  *
******************************************************/

int	is_valid(char *check, char *mesure)
{
	int	i;

	i = 0;
	while (check[i])
	{
		if (check_char(check[i], mesure[i]) != 0
			&& check_char(check[i], mesure[i]) != 32)
			return (1);
		i++;
	}
	return (0);
}

/******************************************************
*  				*  check built-in 1  *
******************************************************/

int	buildin_cmd(t_mcmd *command, int i, int fd)
{
	if (!ft_strcmp(command->av[0], "export"))
	{
		new_export(command, fd);
		return (1);
	}
	else if (!is_valid(command->av[0], "ENV"))
	{
		exp_envp(command->en, command->out, fd);
		return (1);
	}
	else if (!ft_strcmp(command->av[0], "exit"))
	{
		while (command->av[i])
			i++;
		my_exit(command->ac, i + 1, command->av);
		return (1);
	}
	else if (!ft_strcmp(command->av[0], "unset"))
	{
		init_unset(command);
		return (1);
	}
	return (0);
}

/******************************************************
*  				* check built-in 2  *
******************************************************/

int	ft_builtin(t_mcmd *command, int fd)
{
	int	i;

	i = 0;
	if (buildin_cmd(command, i, fd))
		return (1);
	if (!is_valid(command->av[0], "CD"))
	{
		init_cd(command, 0);
		return (1);
	}
	else if (!is_valid(command->av[0], "PWD"))
	{
		ft_pwd(command, fd);
		return (1);
	}
	else if (!is_valid(command->av[0], "ECHO"))
	{
		my_echo(command->av, command->out, fd);
		return (1);
	}
	return (0);
}
