#include "../minishell.h"

/************************************************************************
*		*		redirect fds for output/input/appending/heredoc		*
************************************************************************/

void	redirect(t_pars *arr, t_mcmd *command)
{
	if (arr->fd_input != 0)
	{
		if (command->in != 0 && close(command->in) == -1)
			perror("fd: in");
		command->in = arr->fd_input;
	}
	if (arr->fd_output != 1)
	{
		if (command->out != 1 && close(command->out) == -1)
			perror("fd: out");
		command->out = arr->fd_output;
	}
}

/************************************************************************
*		*		making a pipes if there's multi command			*
************************************************************************/

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

/************************************************************************
*			*			initiate execute			*
************************************************************************/

void	init_exec(t_mcmd *command)
{
	command->in = 0;
	command->out = 1;
	command->index = 0;
	command->pid = 0;
}

/************************************************************************
*			*			built-in or execution			*
************************************************************************/

void	exec_action(t_mcmd *command, char **args, int flag)
{
	if (command->index == 1 && is_built(command->av[0]))
	{
		flag = 1;
		ft_builtin(command, flag);
	}
	else
		exec(command, args[0], command->en);
}

/************************************************************************
*			*			main in for execute/built-in			*
************************************************************************/

int	ft_exec(t_mcmd *command)
{
	t_pars	cmd;
	int		flag;

	init_exec(command);
	cmd = command->pars;
	while (++command->index < command->ac)
	{
		flag = 0;
		command->av = cmd.args_array->args;
		command->spl_str = cmd.args_array->args;
		if (!command->av[0] || \
			cmd.args_array->fd_input == -1 || cmd.args_array->fd_output == -1)
			return (0);
		fd_pipe(command);
		redirect(cmd.args_array, command);
		exec_action(command, cmd.args_array->args, flag);
		close_fd(command);
		command->in = command->fd[0];
		cmd.args_array = cmd.args_array->next;
	}
	ft_waitpid(command);
	return (0);
}