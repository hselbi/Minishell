#include "../minishell.h"

/**************************************************************************
*			*          check if there's equality symbol		      *					  
***************************************************************************/

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

/**************************************************************************
*	*          check how many equalities symbol are there		      *					  
***************************************************************************/

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

/**************************************************************************
*		*          check if it is forbidden character		      *					  
***************************************************************************/

int	char_valid(char c)
{
	if (c == '-')
		return (2);
	else if (c == '!')
		return (4);
	else if (ft_isdigit(c))
		return (1);
	else if (c == '#')
		return (3);
	return (0);
}
