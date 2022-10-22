#include "../minishell.h"

/******************************************************
*  		*  print error if it's not there  *
******************************************************/

char	*cd_arg(t_mcmd *command, int i, char *buf)
{
	char	*s;

	if (!ft_strncmp(command->av[i + 1], ".", 1))
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

/******************************************************
*  				*	get from my env		*
******************************************************/

char	*my_getenv(t_list *env, int i)
{
	char	*str;
	t_list	*tmp;
	char	**spl;

	tmp = env;
	while (i-- > 1)
		tmp = tmp->next;
	spl = ft_split(tmp->content, '=');
	if (!spl[1])
	{
		str = ft_strdup(".");
		free_two(spl, 1);
	}
	else
	{
		str = ft_strdup(tmp->content + 5);
		free_two(spl, 1);
	}
	return (str);
}

/******************************************************
*  			*	only cd without args	 *
******************************************************/

void	cd_only(t_mcmd *command, char *buf)
{
	int	i;

	i = check_var("HOME", command->en);
	if (i > 0)
		buf = my_getenv(command->en, i);
	else
		buf = NULL;
	if (chdir(buf) == -1)
	{
		g_status = 1;
		printf("cd: HOME not set\n");
	}
}

/******************************************************
*  			*	process of cd function	 *
******************************************************/

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
		cd_only(command, buf);
		getcwd(buffer, sizeof(buffer));
	}
	if (!buf)
		free(buf);
	if (check_var("PWD", command->en))
	{
		adding_oldpath(command, ori_path);
		adding_newpath(command, buffer);
		ft_free(command->av);
	}
	free(ori_path);
}

/******************************************************
*  				*  main cd function  *
******************************************************/

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
