/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:53:45 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/26 11:59:35 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************************************************
*		*		convert envp(linked list) to env(2d arr)		*
************************************************************************/

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

/************************************************************************
*		*			starting action for execusion			*
************************************************************************/

void	ft_excusion(char *cmd, t_mcmd *command, char *en[])
{
	int	i;

	i = 0;
	(void)cmd;
	while (command->spl_str[i++] != NULL)
		command->ac_spl++;
	if (!ft_strncmp(ft_strchr(command->spl_str[0], '/'), "/", 1))
		is_cmd_path(command->spl_str, command->spl_str[0], en);
	else
	{
		command->path = make_path(command->spl_str[0], en);
		printf("test haid\n");
		if (!(command->path) && !is_built(command->spl_str, i))
		{
			free(command->path);
			exit_error(127, "Error: Command not found");
		}
		else if (is_built(command->av, command->ac_spl) && !ft_builtin(command, 0))
		{
			// check this for env handling
			if (execve(command->path, command->spl_str, en) == -1)
				exit_error(127, "Error: Command cannot execute");
		}
		if (command->path != NULL)
			free(command->path);
		exit(0);
	}
}

/************************************************************************
*		*		forking and duplicate for execusion			*
************************************************************************/

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
		signal(SIGQUIT, SIG_DFL);
		printf("test 0\n");
		ft_excusion(str, command, envp);
		ft_free(envp);
	}
}
