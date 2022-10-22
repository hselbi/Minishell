#include "../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	p_free(t_mcmd *command)
{
	int	i;

	i = 0;
	while (command->pars.args_array)
	{
		i = 0;
		while (command->pars.args_array->args[i])
		{
			free(command->pars.args_array->args[i]);
			command->pars.args_array->args[i] = NULL;
			i++;
		}
		free(command->pars.args_array->args);
		command->pars.args_array->args = NULL;
		command->pars.args_array = command->pars.args_array->next;
	}
	free(command->pars.args_array);
	command->pars.args_array = NULL;
}

void	free_two(char **str, int i)
{
	if (i == 0)
	{
		if (str[0])
		{
			free(str[0]);
			str[0] = NULL;
			free(str[1]);
			str[1] = NULL;
			free(str);
			str = NULL;
		}
	}
	else
	{
		if (str[0])
		{
			free(str[0]);
			free(str[1]);
			free(str);
		}
	}
}

void	free_all(t_mcmd *command)
{
	int	i;

	i = 0;
	while (command->av[i])
	{
		free(command->av[i]);
		command->av[i] = NULL;
		i++;
	}
	free(command->av);
	command->av = NULL;
}

void	exit_error(int code, char *error)
{
	puts(error);
	exit(code);
}