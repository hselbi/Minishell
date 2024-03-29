#include "../minishell.h"

void	adding_newpath(t_mcmd *command, char *new_path)
{
	command->av = (char **)malloc(sizeof(char *) * 3);
	command->av[0] = ft_strdup("export");
	command->av[1] = ft_strjoin("PWD=", new_path);
	command->av[2] = NULL;
	new_export(command);
	free_two(command->av, 0);
}

void	adding_oldpath(t_mcmd *command, char *ori_path)
{
	command->av = (char **)malloc(sizeof(char *) * 3);
	command->av[0] = ft_strdup("export");
	command->av[1] = ft_strjoin("OLDPWD=", ori_path);
	command->av[2] = NULL;
	new_export(command);
	free_two(command->av, 0);
}

char	*cd_arg(t_mcmd *command, int i, char *buf)
{
	char	*s;

	if (!ft_strcmp(command->av[i + 1], "."))
	{
		s = getcwd(NULL, 0);
		if (!s)
		{
			printf("cd: error retrieving current directory: getcwd: cannot");
			printf(" access parent directories: No such file or directory\n");
			free(s);
		}
		free(s);
		return (buf);
	}
	else
	{
		if (chdir(command->av[i + 1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", command->av[i + 1]);
		}
		buf = getcwd(NULL, 0);
		return (buf);
	}
}

void	my_cd(t_mcmd *command, int ac)
{
	char	buffer[1024];
	char	*buf;
	char	*ori_path;

	getcwd(buffer, sizeof(buffer));
	buf = buffer;
	ori_path = ft_strdup(buffer);
	if (ac >= 3)
		buf = cd_arg(command, 0, buf);
	else if (ac == 2)
	{
		if (check_var("HOME", command->en))
			buf = getenv("HOME");
		else
			buf = NULL;
		if (chdir(buf) == -1)
		{
			g_status = 1;
			printf("cd: HOME not set\n");
		}
		getcwd(buffer, sizeof(buffer));
	}
	if (check_var("PWD", command->en))
	{
		adding_oldpath(command, ori_path);
		adding_newpath(command, buffer);
	}
	free(ori_path);
}

int	init_cd(t_mcmd *command, int i)
{
	int	ac;

	i = 0;
	ac = 1;
	while (command->av[i])
	{
		ac++;
		i++;
	}
	my_cd(command, ac);
	return (1);
}
