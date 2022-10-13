#include "../minishell.h"
// #include "../libft/libft.h"
#include <string.h>


#include "../minishell.h"
/*size of current directory*/

char	**files_tab(int len);
char	*pref(char *str);
char	*suf(char *str);
char	*strjoin_free(char *s1, char const *s2);
int	check_su(char *str, char *su);


int	current_dir(void)
{
	struct dirent	*ptr_dirent;
	DIR				*ptr_dir;
	int				i;

	i = 0;
	ptr_dir = opendir("./");
	if (ptr_dir == NULL)
		return (0);
	ptr_dirent = readdir(ptr_dir);
	while (ptr_dirent)
	{
		ptr_dirent = readdir(ptr_dir);
		i++;
	}
	closedir(ptr_dir);
	return (i);
}
/******************************************/

int	array_wood(void)
{
	struct dirent	*ptr_dirent;
	DIR				*ptr_dir;
	int				i;

	i = 0;
	ptr_dir = opendir("./");
	if (ptr_dir == NULL)
		return (0);
	ptr_dirent = readdir(ptr_dir);
	while (ptr_dirent)
	{
		ptr_dirent = readdir(ptr_dir);
		i++;
	}
	closedir(ptr_dir);
	return (i);
}

/******************************************/

void	free_star(char *pre, char *su, char **arr)
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
/******************************************/

char	*wc_parser(char *str, int i, char *out, char **arr)
{
	char	*su;
	char	*pre;

	arr = files_tab(i);
	if (!str || i == 0 || !arr)
		return (NULL);
	pre = pref(str);
	su = suf(str);
	out = ft_strdup("");
	i = 0;
	while (arr[i])
	{
		if (!pre && !su)
			out = strjoin_free(out, arr[i]);
		else if (pre && !ft_strncmp(pre, arr[i] + 1, ft_strlen(pre)) && !su)
			out = strjoin_free(out, arr[i]);
		else if (su && !pre && check_su(arr[i], su))
			out = strjoin_free(out, arr[i]);
		else if (check_su(arr[i], su)
			&& !ft_strncmp(pre, arr[i] + 1, ft_strlen(pre)))
			out = strjoin_free(out, arr[i]);
		i++;
	}
	free_star(pre, su, arr);
	return (out);
}
/******************************************/

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
	k = 0;
	while (s2[k])
	{
		res[i] = s2[k];
		i++;
		k++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
/******************************************/

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
/******************************************/

char	*pref(char *str)
{
	char	*res;
	int		i;

	if (str && str[0] == '*')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '*')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/******************************************/

char	*suf(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = ft_strlen(str) - 1;
	if (str && str[i] == '*')
		return (NULL);
	j = 0;
	while (i >= 0 && str[i] != '*')
	{
		j++;
		i--;
	}
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[++i])
	{
		res[j] = str[i];
		j++;
	}
	res[i] = '\0';
	return (res);
}
/******************************************/

int	check_su(char *str, char *su)
{
	int	i;
	int	j;

	if (!str || !su)
		return (0);
	i = ft_strlen(str) - 3;
	j = ft_strlen(su) - 1;
	while (i >= 0 && j >= 0)
	{
		if (str[i] != su[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

/******************************************/

char	**files_tab(int len)
{
	struct dirent	*ptr_dirent;
	DIR				*ptr_dir;
	char			**res;
	int				i;

	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	ptr_dir = opendir("./");
	if (ptr_dir == NULL)
		return (NULL);
	ptr_dirent = readdir(ptr_dir);
	while (ptr_dirent)
	{
		if (ptr_dirent->d_name[0] != '.')
		{
			res[i] = ft_strdup2(ptr_dirent->d_name);
			i++;
		}
		ptr_dirent = readdir(ptr_dir);
	}
	closedir(ptr_dir);
	res[i] = NULL;
	return (res);
}
/******************************************/

int start_finder(char *str, int i)
{
    while(i >= 0)
    {
        if (str[i] == ' ')
            return(i + 1);
        i--;
    }
    return(0);
}
/******************************************/

int finish_finder(char *str, int i)
{
    while(str[i])
    {
        if (str[i] == ' ')
            return(i);
        i++;
    }
    return(0);
}
/******************************************/

char    *wc_replace(char *line, int i)
{
    int beg;
    int end;
    static char    *ast;
    static char    *put_back;

    beg = start_finder(line, i);
    end = finish_finder(line, i);
    ast = ft_substr(line, beg, end - beg);
    if(!ast)
        return (line);
    put_back = wc_parser(ast, array_wood(), NULL, NULL);;
    if (!put_back)
		return (line);
	put_back = strjoin_free(put_back, line + end);
	line[beg] = '\0';
	line = strjoin_free(line, put_back);
	free(put_back);
	free(ast);
	return (line);
}

int main(int ac, char *av[])
{
	int i = 1;
	char *str = av[1];
	while (*(str + i))
	{
		if (*(str + i) == '*')
		{
			str = wc_replace(str, i);
			i++;
		}
		else
			i++;
		fprintf(stderr, "==> [%s]\n", str);
	}
	return 0;
}


// char	*replace_star(char *str, int i)
// {
// 	int			start;
// 	int			end;
// 	static char	*star;
// 	static char	*replace;

// 	start = find_start(str, i);
// 	end = find_end(str, i);
// 	star = ft_substr(str, start, end - start);
// 	if (!star)
// 		return (str);
// 	replace = parse_star(star, array_wood(), NULL, NULL);
// 	if (!replace)
// 		return (str);
// 	replace = ft_strjoin_free(replace, str + end);
// 	str[start] = '\0';
// 	str = ft_strjoin_free(str, replace);
// 	free(replace);
// 	free(star);
// 	return (str);
// }
/******************************************/

// char    *wc_pars(char *line)
// {
//     int i = 0;

//     while (*(line + i))
// 	{
// 		if (*(line + i) == '*')
// 		{
// 			line = wc_replace(line, i);
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
//     return (line);
// }