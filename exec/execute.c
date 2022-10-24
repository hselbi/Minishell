#include "../minishell.h"

char	**en_conv(t_list *envp)
{
	char	**en;
	t_list	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	en = (char **)malloc(sizeof(char *) * (ft_lstsize(envp) + 1));
	if (!en)
		return (NULL);
	while (tmp != NULL && i < (ft_lstsize(envp) + 2))
	{
		en[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	en[i] = NULL;
	return (en);
}

void	exec(t_mcmd *command, char *str, t_list *en)
{
	int		i;
	char	**envp;

	i = 0;
	command->pid = fork();
	if (command->pid == -1)
	{
		perror("FORK");
		return ;
	}
	else if (command->pid == 0)
	{
		if (command->fd[0] != -1 && (close(command->fd[0]) == -1))
			perror("failed in reading");
		dup2(command->out, 1);
		dup2(command->in, 0);
		if (command->out != 1 && close(command->out) == -1)
			perror("fd: out");
		if (command->in != 0 && close(command->in) == -1)
			perror("fd: in");
		envp = en_conv(en);
		ft_excusion(str, command, envp);
		ft_free(envp);
	}
}

void	redirect(t_pars *arr, t_mcmd *command)
{
	if (arr->fd_input != 0)
	{
		if (command->in != 0 && close(command->in) == -1)
			perror("fd: in");
		command->in = arr->fd_input;
		close(arr->fd_input);
	}
	if (arr->fd_output != 1)
	{
		if (command->out != 1 && close(command->out) == -1)
			perror("fd: out");
		command->out = arr->fd_output;
		close(arr->fd_output);
	}
}

void	fd_pipe(t_mcmd *command)
{
	if (command->ac == 2 || command->index + 1 == command->ac)
	{
		command->fd[0] = -1;
		command->fd[1] = 1;
		command->out = 1;
	}
	else
	{
		if (pipe(command->fd))
			perror("PIPE");
		command->out = command->fd[1];
	}
}

void	close_fd(t_mcmd *command)
{
	if (command->out != 1 && close(command->out) == -1)
		perror("fd: out");
	if (command->in != 0 && close(command->in) == -1)
		perror("fd: in");
}

void	init_exec(t_mcmd *command)
{
	command->in = 0;
	command->out = 1;
	command->index = 0;
	command->pid = 0;
}

int	ft_exec(t_mcmd *command)
{
	t_pars	cmd;
	int		flag;

	cmd = command->pars;
	init_exec(command);
	while (++command->index < command->ac)
	{
		flag = 0;
		command->av = cmd.args_array->args;
		printf("in while 0 %p \n", cmd.args_array->args);
		command->spl_str = cmd.args_array->args;
		if (!command->av[0] || \
			cmd.args_array->fd_input == -1 || cmd.args_array->fd_output == -1)
			return (0);
		printf("in while 1 %p \n", cmd.args_array->args);
		fd_pipe(command);
		redirect(cmd.args_array, command);
		printf("in while 2 %p \n", cmd.args_array->args);
		if (command->index == 1 && is_built(command->av[0]))
		{
			flag = 1;
			printf(">>>>>>>>>>>>%p\n", command->pars.args_array);
			ft_builtin(command, flag);
			printf("in while 3 %p \n", cmd.args_array->args);
		}
		else
			exec(command, cmd.args_array->args[0], command->en);
		close_fd(command);
		command->in = command->fd[0];
		cmd.args_array = cmd.args_array->next;
	}
	ft_waitpid(command);
	return (0);
}
