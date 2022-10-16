#include "../minishell.h"

/******************************************************
*  * give the position of that preticular variables *
******************************************************/

int	check_var(char *str, t_list *en)
{
	t_list	*tmp;
	char	**s;
	int		i;

	i = 1;
	tmp = en;
	if (!tmp || !(tmp->content))
		return (0);
	while (tmp != 0)
	{
		s = ft_split(tmp->content, '=');
		if (!ft_strcmp(str, s[0]))
		{
			free_two(s, 0);
			return (i);
		}
		i++;
		free_two(s, 1);
		tmp = tmp->next;
	}
	// free_two(s, 1);
	return (0);
}

/******************************************************
*			*	remove variable in env	*
******************************************************/

t_list	*my_unset(int ac, char **av, t_list *en)
{
	int		l;
	t_list	*tmp_en;
	t_list	*tmp;
	t_list	*lst;

	l = 0;
	tmp_en = en;
	if (ac >= 3 && !ft_strcmp(av[0], "unset"))
	{
		l = check_var(av[1], en);
		if (l == 1)
		{
			tmp = NULL;
			tmp_en = en;
			en = en->next;
			ft_lstdelone(tmp_en, free);
		}
		else if (l > 1)
		{
			while (l-- > 1)
			{
				if (l == 1)
					lst = tmp_en;
				tmp_en = tmp_en->next;
			}
			tmp = tmp_en->next;
			lst->next = tmp;
		}
	}
	return (en);
}

/******************************************************
*			*	main of unset	*
******************************************************/

void	init_unset(t_mcmd *command)
{
	int	i;

	i = 0;
	while (command->av[i])
		i++;
	command->en = my_unset(i + 1, command->av, command->en);
	command->exp_en = my_unset(i + 1, command->av, command->exp_en);
}
