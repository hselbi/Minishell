#include "../minishell.h"

/************************************************************************
* 						check is a built-in								*
************************************************************************/

int	is_built(char *str)
{
	if (!ft_strcmp(str, "export"))
		return (1);
	else if (!is_valid(str, "ENV"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!is_valid(str, "CD"))
		return (1);
	else if (!is_valid(str, "PWD"))
		return (1);
	else if (!is_valid(str, "ECHO"))
		return (1);
	return (0);
}

void	is_cmd_path(char **path, char *cmd, char *en[])
{
	if (cmd && !ft_strncmp(cmd, "/", 1))
	{
		if (!access(cmd, F_OK) || !access(cmd, X_OK))
		{
			if (execve(cmd, path, en) == -1)
			{
				puts("Error in exceve\n");
				exit(127);
			}
		}
		else
		{
			printf("%s: No such file or directory\n", cmd);
			ft_free(path);
			exit(127);
		}
	}
}

char	*correct_one(char **paths, char *cmd)
{
	char	*str;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		command = ft_strjoin(str, cmd);
		free(str);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (0);
}

char	*make_path(char *cmd, char *en[])
{
	char	*line;
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	while (en[i] && ft_strncmp("PATH", en[i], 4))
		i++;
	if (en[i] == NULL)
	{
		puts("Error: Path has been removed\n");
		exit(127);
	}
	line = ft_strdup(en[i] + 5);
	paths = ft_split(line, ':');
	free(line);
	result = correct_one(paths, cmd);
	if (result == NULL || !result)
	{
		ft_free(paths);
		return (NULL);
	}
	ft_free(paths);
	return (result);
}

void	ft_excusion(char *cmd, t_mcmd *command, char *en[])
{
	int	i;

	i = 0;
	(void)cmd;
	while (command->spl_str[i++] != NULL)
		command->ac_spl++;
	if ((command->spl_str[0] && (!ft_strncmp(command->spl_str[0], "/", 1))))
		is_cmd_path(command->spl_str, command->spl_str[0], en);
	else
	{
		command->path = make_path(command->spl_str[0], en);
		if (!(command->path) && !is_built(command->spl_str[0]))
		{
			free(command->path);
			puts("Error: Command not found");
			exit(127);
		}
		else if (!ft_builtin(command, 0))
		{
			if (execve(command->path, command->spl_str, en) == -1)
			{
				puts("Error: Command cannot execute");
				exit(127);
			}
		}
		if (command->path != NULL)
			free(command->path);
		exit(0);
	}
}
