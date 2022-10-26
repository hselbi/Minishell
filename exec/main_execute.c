/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:48 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 22:03:48 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************************************************
*		*		redirect fds for output/input/appending/heredoc		*
************************************************************************/

int	redirect(t_pars *arr, t_mcmd *command)
{
	command->d = 0;
	if (arr->fd_input != 0 && arr->fd_input != -1)
	{
		if (command->in != 0 && close(command->in) == -1)
			perror("fd: in");
		command->in = arr->fd_input;
		command->d = 1;
	}
	if (arr->fd_output != 1 && arr->fd_output != -1)
	{
		if (command->out != 1 && close(command->out) == -1)
			perror("fd: out");
		command->out = arr->fd_output;
		command->d = 1;
	}
	return (command->d);
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
	int	i;

	i = 0;
	if (command->ac == 2 && is_built(command->av, i))
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
		arg_inout(command, cmd.args_array->fd_input, cmd.args_array->fd_output);
		fd_pipe(command);
		command->d = redirect(cmd.args_array, command);
		if (command->d != -1)
		{
			exec_action(command, cmd.args_array->args, flag);
			close_fd(command);
		}
		command->in = command->fd[0];
		cmd.args_array = cmd.args_array->next;
	}
	ft_waitpid(command);
	return (0);
}
