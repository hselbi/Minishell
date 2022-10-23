#include "../minishell.h"

/******************************************************
*  		*  check if str is valid identification  *
******************************************************/

int	h_check_av2(char **str, int i)
{
	if (str[0][i] != '_' && !ft_isdigit(str[0][i]) && !ft_isalpha(str[0][i]))
	{
		ft_free(str);
		return (1);
	}
	return (0);
}

int	h_check_av(char **str, int k)
{
	int		i;

	i = 0;
	while (str[0][i])
	{
		if (i == 0)
		{
			k = char_valid(str[0][i]);
			if (k > 0)
			{
				ft_free(str);
				return (k);
			}
			else
			{
				if (str[0][i] == '$')
					i++;
			}	
		}
		if (h_check_av2(str, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_av(char *av)
{
	char	**str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	str = ft_split(av, '=');
	if (str[0] == NULL)
	{
		free(str);
		return (1);
	}	
	i = h_check_av(str, k);
	printf("test %d\n", i);
	if (i)
		return (i);
	ft_free(str);
	return (0);
}

/******************************************************
*  				*  main cd function  *
******************************************************/

int	h_sel_env(t_list *tmp, t_list **en, char *s, char **str)
{
	if (tmp != NULL && !ft_strcmp(str[0], s))
	{
		free_two(str, 1);
		*en = tmp->next;
		free(tmp);
		return (1);
	}
	return (0);
}

void	sel_env(char *s, t_list **en)
{
	t_list	*tmp;
	t_list	*prev;
	char	**str;

	tmp = *en;
	str = ft_split(tmp->content, '=');
	if (h_sel_env(tmp, en, s, str))
		return ;
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
	ft_lstdelone(tmp, free);
	free_two(str, 1);
}
