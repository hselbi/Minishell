#include "../minishell.h"

/******************************************************
*  				*  main cd function  *
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
*  				*  main cd function  *
******************************************************/

void	sel_env(char *s, t_list **en)
{
	t_list	*tmp;
	t_list	*prev;
	char	**str;

	tmp = *en;
	str = ft_split(tmp->content, '=');
	if (tmp != NULL && !ft_strcmp(str[0], s))
	{
		free_two(str, 1);
		*en = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(str[0], s))
	{
		free_two(str, 0);
		prev = tmp;
		tmp = tmp->next;
		str = ft_split(tmp->content, '=');
	}
	if (tmp == NULL)
	{
		free_two(str, 1);
		return ;
	}
	prev->next = tmp->next;
	free(tmp);
	free_two(str, 1);
}

/******************************************************
*  				*  main cd function  *
******************************************************/

int	check_av(char *av)
{
	char	**str;
	int		i;
	int		k;

	i = 0;
	str = ft_split(av, '=');
	if (str[0] == NULL)
	{
		free(str);
		return (1);
	}
	while (str[0][i])
	{
		if (i == 0)
		{
			k = char_valid(str[0][i]);
			if (k > 0)
			{
				// free_two(str, 1);
				return (k);
			}
			else
			{
				if (str[0][i] == '$')
					i++;
			}	
		}
		if (str[0][i] != '_' &&
			!ft_isdigit(str[0][i]) && !ft_isalpha(str[0][i]))
		{
			free_two(str, 1);
			return (1);
		}
		i++;
	}
	free_two(str, 1);
	return (0);
}

/******************************************************
*  				*  main cd function  *
******************************************************/

void	not_many_eq(t_mcmd *command, int i)
{
	int	j;
	int	k;

	k = check_var(command->av[i], command->en);
	j = check_var(command->av[i], command->exp_en);
	if (k)
		sel_env(command->av[i], &command->exp_en);
	if (j)
		sel_env(command->av[i], &command->en);
	ft_lstadd_back(&command->exp_en, ft_lstnew(command->av[i]));
}

/******************************************************
*  				*  main cd function  *
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
*  				*  main cd function  *
******************************************************/

void	export_new(t_mcmd *command, int i, int s, int flag)
{
	if (s == 1 || s == 4)
	{
		if (s == 1)
			printf("export: `%s': not a valid identifier\n",
				command->av[i]);
		else
			printf("%s: event not found\n", command->av[i]);
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
*  				*  main cd function  *
******************************************************/

void	new_export(t_mcmd *command, int flag)
{
	int	i;
	int	ac;
	int	s;

	i = 1;
	ac = 1;
	while (command->av[ac])
		ac++;
	if (ac >= 2 && !ft_strcmp(command->av[0], "export"))
	{
		while (i < ac)
		{
			s = check_av(command->av[i]);
			if (s == 2)
			{
				printf("export: %s: invalid option\n", command->av[i]);
				break ;
			}
			else
				export_new(command, i, s, flag);
			i++;
		}
	}
	else if ((ac == 1) && !ft_strcmp(command->av[0], "export"))
	{
		exp_sorting(command->exp_en, command->out, flag);
		g_status = 0;
	}
}
