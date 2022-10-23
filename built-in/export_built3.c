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
	return (0);
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

/******************************************************
*  				*  main cd function  *
******************************************************/

void	not_many_eq(t_mcmd *command, int i)
{
	int	j;
	int	k;

	printf("test hafid\n");
	k = check_var(command->av[i], command->en);
	j = check_var(command->av[i], command->exp_en);
	if (k)
		sel_env(command->av[i], &command->exp_en);
	if (j)
		sel_env(command->av[i], &command->en);
	ft_lstadd_back(&command->exp_en, ft_lstnew(command->av[i]));
}
