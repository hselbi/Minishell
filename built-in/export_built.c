#include "../minishell.h"

/******************************************************
*  		*  sorting the linked list for export   *
******************************************************/

void	exp_sorting(t_list *en, int fd, int flag)
{
	t_list	*tmp;
	char	*str;
	int		len;
	int		i;

	tmp = en;
	len = ft_lstsize(en);
	i = 0;
	while (i < len)
	{
		tmp = en;
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->content, tmp->next->content) > 0)
			{
				str = tmp->content;
				tmp->content = tmp->next->content;
				tmp->next->content = str;
			}
			tmp = tmp->next;
		}
		i++;
	}
	fix_list(en, fd, flag);
}

/******************************************************
*  		*  check if there's too many eq or not*
******************************************************/

void	valid_exp(t_mcmd *command, int i)
{
	char	**str;
	int		j;
	int		k;

	if (many_eq(command->av[i]))
	{
		str = ft_split(command->av[i], '=');
		free(str[1]);
		str[1] = ft_strchr(command->av[i], '=');
		str[1]++;
		j = check_var(str[0], command->en);
		k = check_var(str[0], command->exp_en);
		if (j)
			sel_env(str[0], &command->en);
		if (k)
			sel_env(str[0], &command->exp_en);
		ft_lstadd_back(&command->en, ft_lstnew(command->av[i]));
		ft_lstadd_back(&command->exp_en, ft_lstnew(command->av[i]));
		free(str[0]);
		str[0] = NULL;
		free(str);
		str = NULL;
	}
	else
		not_many_eq(command, i);
}

/******************************************************
*  			*  check if it's valid or not  *
******************************************************/

void	export_new(t_mcmd *command, int i, int s, int flag)
{
	if (s == 1 || s == 4)
	{
		if (s == 1)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(command->av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			ft_putstr_fd(command->av[i], 2);
			ft_putstr_fd(": event not found\n", 2);
		}
		g_status = 1;
	}
	else if (s == 0)
	{
		valid_exp(command, i);
		g_status = 0;
	}
	else if (s == 3)
	{
		exp_sorting(command->exp_en, command->out, flag);
		g_status = 0;
	}
}

/******************************************************
*	*	main export (with args or without args)	*
******************************************************/

void	export_args(t_mcmd *command, int flag, int ac)
{
	int	i;
	int	s;

	i = 1;
	while (i < ac)
	{
		s = check_av(command->av[i]);
		if (s == 2)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(command->av[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			break ;
		}
		else
			export_new(command, i, s, flag);
		i++;
	}
}

void	new_export(t_mcmd *command, int flag)
{
	int	ac;

	ac = 1;
	while (command->av[ac])
		ac++;
	if (ac >= 2 && !ft_strcmp(command->av[0], "export"))
		export_args(command, flag, ac);
	else if ((ac == 1) && !ft_strcmp(command->av[0], "export"))
	{
		exp_sorting(command->exp_en, command->out, flag);
		g_status = 0;
	}
}
