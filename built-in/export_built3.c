#include "../minishell.h"

/*	check if there's "=" return pos	*/

int	check_eq(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

/*		check how many "="		*/

int	many_eq(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (j > 0 && ft_isalpha(str[i]))
			return (j);
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}
