#include "../minishell.h"

void	free_ast(char *pre, char *su, char **arr)
{
	int	i;

	i = 0;
	if (su)
		free(su);
	if (pre)
		free(pre);
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

char	*strjoin_free(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		k;

	if (!s1 || !s2)
		return ((void *)0);
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return ((void *)0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	free(s1);
	k = 0;
	while (s2[k])
	{
		res[i] = s2[k];
		i++;
		k++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup2(char *str)
{
	char	*res;
	int		len;
	int		i;

	i = 1;
	len = ft_strlen(str);
	res = (char *) malloc(len + 4);
	if (res == (void *)0)
		return ((void *)0);
	res[0] = 39;
	while (str[i - 1])
	{
		res[i] = str[i - 1];
		i++;
	}
	res[i] = 39;
	res[i + 1] = ' ';
	res[i + 2] = '\0';
	return (res);
}
