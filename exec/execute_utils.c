/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:42 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 19:03:05 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************************************************
* 	*						check is a built-in						*
************************************************************************/

int	is_built(char **str, int i)
{
	i = 0;
	while (str[i])
		i++;
	if (!ft_strcmp(str[0], "export"))
		return (1);
	else if (i == 1 && !ft_strcmp(str[0], "env"))
		return (1);
	else if (!ft_strcmp(str[0], "exit"))
		return (1);
	else if (!ft_strcmp(str[0], "unset"))
		return (1);
	else if (!ft_strcmp(str[0], "cd"))
		return (1);
	else if (!ft_strcmp(str[0], "pwd"))
		return (1);
	else if (!ft_strcmp(str[0], "echo"))
		return (1);
	return (0);
}

/************************************************************************
*			*			check cmd is a path				*
************************************************************************/

void	is_cmd_path(char **path, char *cmd, char *en[])
{
	struct stat	stats;

	if (!stat(cmd, &stats))
	{
		if (S_ISREG(stats.st_mode))
		{
			if (execve(cmd, path, en) == -1)
				exit_error(127, "Error: Command cannot execute");
		}
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			ft_free(path);
			exit(126);
		}
	}
	else
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Not a directory\n", 18);
		exit(126);
	}
}

/************************************************************************
*			*			check cmd is a path				*
************************************************************************/

char	*correct_one(char **paths, char *cmd)
{
	char	*str;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (!i && (paths[i][0] != '/'))
			return (NULL);
		str = ft_strjoin(paths[i], "/");
		command = ft_strjoin(str, cmd);
		free(str);
		if (!access(command, F_OK) && !access(command, X_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

/************************************************************************
*			*			making a path				*
************************************************************************/

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
		exit_error(127, "Error: Path has been removed");
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

/************************************************************************
*				*			closing fds			*
************************************************************************/

void	close_fd(t_mcmd *command)
{
	if (command->out != 1 && close(command->out) == -1)
		perror("fd: out");
	if (command->in != 0 && close(command->in) == -1)
		perror("fd: in");
}
