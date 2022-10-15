#include "../minishell.h"

int	check_char(char c1, char c2)
{
	return (c1 - c2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	isspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 32)
			return (0);
		i++;
	}
	return (1);
}

/************************************************************************
* 					check a spaces in a string							*
************************************************************************/

int	spaces_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}