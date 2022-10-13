#include "../minishell.h"

char	*wild_path(char *s)
{
	int		i;
	char	*out;

	i = 0;
    out = (char *)malloc(ast_strlen(s, '*') + 2);
    if (!out)
		return (NULL);
	while (s[i] && (s[i] == '/' || s[i] == '.'))
	{
		out[i] = s[i];
		i++;
	}
	if (i == 0 || s[i - 1] == '/')
	{
		out[i] = '.';
		i++;
	}
	out[i] = '\0';
	return (out);
}

/*********************************************/

size_t		ast_strlen(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*********************************************/

int		is_asterisk(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*********************************************/

int		s_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '/' && i != 0)
			count++;
		i++;
	}
	return (count);
}

/*********************************************/

int		str_match(char *s1, char *s2, int i, int j)
{
	int	k;

	if ((!s1[i] || (!s1[i + 1] && s1[i] == '*')) && !s2[j])
		return (1);
	if (!s2[j])
		return (0);
	if (s1[i] == s2[j])
		return (str_match(s1, s2, i + 1, j + 1));
	k = j;
	if (s1[i] == '*')
		while (s2[k])
			if (str_match(s1, s2, i + 1, k++))
				return (1);
	if (s1[i] == '*' && s1[i + 1] == s2[j + 1])
		return (str_match(s1, s2, i + 1, j + 1));
	if (s1[i] == '*')
		return (str_match(s1, s2, i, j + 1));
	return (0);
}

/**********************************************/

int		is_strequ(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
