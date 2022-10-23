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
			ft_free(s);
			return (i);
		}
		else
			ft_free(s);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

/******************************************************
*			*	remove variable in env	*
******************************************************/
void	h_unset(int l, t_list *tmp_en)
{
	t_list	*tmp;
	t_list	*lst;

	while (l-- > 1)
	{
		if (l == 1)
			lst = tmp_en;
		tmp_en = tmp_en->next;
	}
	tmp = tmp_en->next;
	lst->next = tmp;
	ft_lstdelone(tmp_en, free);
}

t_list	*my_unset(char *str, t_list **en)
{
	int		l;
	t_list	*tmp_en;

	l = 0;
	tmp_en = *en;
	l = check_var(str, *en);
	if (l == 1)
	{
		tmp_en = *en;
		en = &(tmp_en->next);
		ft_lstdelone(tmp_en, free);
	}
	else if (l > 1)
		h_unset(l, tmp_en);
	return (*en);
}

/******************************************************
*			*	main of unset	*
******************************************************/

void	init_unset(t_mcmd *command)
{
	int	i;
	int	s;
	int	eq;

	i = 1;
	while (command->av[i])
	{
		eq = check_eq(command->av[i]);
		s = check_av(command->av[i]);
		if (s == 1 || eq)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(command->av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			command->en = my_unset(command->av[i], &command->en);
			command->exp_en = my_unset(command->av[i], &command->exp_en);
		i++;
	}
}
