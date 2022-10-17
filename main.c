#include "minishell.h"

/************************************************************************
*		 		*			path home back-up			*
************************************************************************/
void	save_home(t_mcmd *command)
{
	int		i;
	t_list	*arr;

	i = 0;
	arr = command->en;
	while (arr->content != NULL && ft_strncmp("HOME=", arr->content, 5) != 0)
		arr = arr->next;
	command->home = ft_strdup(arr->content);
}

/************************************************************************
* 		*			check is variable is already in env			*
************************************************************************/

int	check_env(t_list *en, char *s)
{
	t_list	*tmp;
	char	**str;

	tmp = en;
	while (tmp != NULL)
	{
		if (check_eq(tmp->content))
		{
			str = ft_split(tmp->content, '=');
			if (!ft_strcmp(str[0], s))
			{
				free_two(str, 1);
				return (1);
			}
			free_two(str, 0);
		}
		else
		{
			if (!ft_strcmp(tmp->content, s))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/************************************************************************
* 		*			adding OLDPWD if there isn't one			*
************************************************************************/

void	init_minishell(t_mcmd *command, char **envp)
{
	command->path = NULL;
	command->d = 0;
	command->en = ft_env(envp);
	command->exp_en = ft_env(envp);
	if (!check_env(command->exp_en, "OLDPWD"))
	{
		ft_lstadd_back(&command->exp_en, ft_lstnew("OLDPWD"));
	}
	save_home(command);
}

/************************************************************************
* 		*			wildcard + parsing + execusion			*
************************************************************************/

void	mini_action(t_mish ms, t_mcmd command)
{
	t_pars	tmp;

	ms.line = wc_handle(ms.line);
	if (!check_pipe_error(ms.line)
		&& !check_check(ms.line, &command.pars)
		&& !check_stach_here_doc(ms.line))
	{
		befor_make_struct(ms.line, &command.pars);
		args_pars(command.pars);
		tmp = command.pars;
		while (tmp.args_array)
		{
			command.ac++;
			tmp.args_array = tmp.args_array->next;
		}
		printf("before before %p \n", command.pars.args_array->args);
		ft_exec(&command);
		printf("before %p \n", command.pars.args_array->args);
		// p_free(&command);
	}
	free(ms.line);
}

/************************************************************************
* 		*			main minishell handling inputs			*
************************************************************************/

int	main(int argc, char *argv[], char *envp[])
{
	t_mish	ms;
	t_mcmd	command;
	t_pars	pars;
	int		i;

	(void)argv;
	(void)argc;
	init_minishell(&command, envp);
	pars.env = command.en;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ms.line = readline("\033[1;36mminishell-1.0$ \033[0m");
		if (ms.line)
			add_history(ms.line);
		command.pars = pars;
		i = 0;
		command.ac = 1;
		if (ms.line == NULL || ms.line[0] == '\0' || isspaces(ms.line) == 1)
		{
			if (ms.line == NULL)
			{
				write(2, "exit\n", 5);
				free(ms.line);
				ms.line = NULL;
				exit(1);
			}
			free(ms.line);
			continue ;
		}
		if (ms.line)
			mini_action(ms, command);
		system("leaks minishell");
	}
	return (0);
}
