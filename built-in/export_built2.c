#include "../minishell.h"

/*
? print a string from modefication the parametre string
*/

char	*with_equal(char *str, char **spl_str)
{
	char	*out;
	char	*tmp;

	out = ft_strjoin(str, spl_str[0]);
	free(str);
	str = NULL;
	tmp = ft_strjoin(out, "=\"");
	free(out);
	out = NULL;
	str = ft_strjoin(spl_str[1], "\"");
	out = ft_strjoin(tmp, str);
	free(tmp);
	tmp = NULL;
	free(str);
	str = NULL;
	ft_free(spl_str);
	return (out);
}

char	*without_equal(int i, char *arr, char **spl_str)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin(arr, spl_str[0]);
	free(arr);
	arr = NULL;
	if (i != 0)
		out = ft_strjoin(tmp, "=\"\"");
	else
		out = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	ft_free(spl_str);
	return (out);
}

char	**make_env(int i, char *lst)
{
	char	**str_spl;

	if (i == 1)
	{
		str_spl = ft_split(lst, '=');
		free(str_spl[1]);
		str_spl[1] = ft_strchr(lst, '=');
		str_spl[1]++;
	}
	else if (i > 1)
	{
		str_spl = (char **)malloc(sizeof(char *) * 3);
		if (!str_spl)
			return (NULL);
		str_spl[0] = ft_strdup(ft_substr(lst, 0, check_eq(lst)));
		str_spl[1] = ft_strdup(
				ft_substr(lst, check_eq(lst) + 1, ft_strlen(lst)));
		str_spl[2] = NULL;
	}
	else
		str_spl = ft_split(lst, ' ');
	return (str_spl);
}

void	assemebly_str(char *lst, int fd)
{
	char	*out;
	char	*arr;
	char	**str_spl;
	int		i;

	out = NULL;
	i = 0;
	arr = ft_strdup("declare -x ");
	i = many_eq(lst);
	str_spl = make_env(i, lst);
	if (str_spl[0] && str_spl[1])
	{
		out = with_equal(arr, str_spl);
	}
	else if (str_spl[0] && str_spl[1] == NULL)
	{
		out = without_equal(i, arr, str_spl);
	}
	write(fd, out, ft_strlen(out));
	write(fd, "\n", 1);
	free(out);
	out = NULL;
}

/*
? a loop that passing content of expo_env to function above
*/

void	fix_list(t_list *notComp, int fd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	if (!notComp)
		return ;
	tmp = notComp;
	while (i < ft_lstsize(notComp))
	{
		assemebly_str(tmp->content, fd);
		tmp = tmp->next;
		i++;
	}
}
