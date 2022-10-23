#include "minishell.h"

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
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

/************************************************************************
* 		*			wildcard + parsing + execusion			*
************************************************************************/

void	mini_action(t_mish ms, t_mcmd *command)
{
	t_pars	tmp;

	ms.line = wc_handle(ms.line);
	if (!check_pipe_error(ms.line)
		&& !check_check(ms.line, &command->pars)
		&& !check_stach_here_doc(ms.line))
	{
		befor_make_struct(ms.line, &command->pars);
		tmp = command->pars;
		while (tmp.args_array)
		{
			command->ac++;
			tmp.args_array = tmp.args_array->next;
		}
		ft_exec(command);
	}
	free_args_array(command);
	free(ms.line);
}

/************************************************************************
* 		*			main minishell handling inputs			*
************************************************************************/

int	h_main(t_mish ms)
{
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
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mish	ms;
	t_mcmd	command;
	t_pars	pars;

	(void)argv;
	(void)argc;
	init_minishell(&command, envp);
	pars.env = command.en;
	while (1)
	{
		ms.line = readline("minishell-1.0$ ");
		if (ms.line && *ms.line)
			add_history(ms.line);
		command.pars = pars;
		command.ac = 1;
		if (h_main(ms))
			continue ;
		if (ms.line)
			mini_action(ms, &command);
	}
	return (0);
}
