#include "../minishell.h"

int	check_option(char *str)
{
	if (!str)
		return (1);
	if (*str == '\\')
		str++;
	if (*str == '-' && *str)
	{
		str++;
		if (*str == '\\')
			str++;
		if (*str != 'n')
			return (1);
		while (*str != '\0')
		{
			if (*str != 'n')
				return (1);
			else
				str++;
		}
		return (0);
	}
	return (1);
}

void	print_echo(char *str, int flag, int fd, int type)
{
	if (type == 1)
	{
		if (flag == 1)
			write(fd, str, ft_strlen(str));
		else
			printf("%s", str);
	}
	else
	{
		if (flag == 1)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
		else
			printf("%s\n", str);
	}
}

void	with_option(int fd, char *str[], int i, int flag)
{
	char	*s1;
	char	*s2;

	s1 = ft_strdup(str[i++]);
	if (!s1)
		return ;
	while (str[i])
	{
		s2 = ft_strjoin(s1, " ");
		free(s1);
		s1 = NULL;
		s1 = ft_strjoin(s2, str[i]);
		free(s2);
		s2 = NULL;
		i++;
	}
	print_echo(s1, flag, fd, 1);
	free(s1);
}

void	without_option(int fd, char *str[], int i, int flag)
{
	char	*s1;
	char	*s2;

	i = 1;
	if (str[i] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	s1 = ft_strdup(str[i++]);
	while (str[i])
	{
		s2 = ft_strjoin(s1, " ");
		free(s1);
		s1 = NULL;
		s1 = ft_strjoin(s2, str[i]);
		free(s2);
		s2 = NULL;
		i++;
	}
	print_echo(s1, flag, fd, 0);
	free(s1);
}

void	my_echo(char *str[], int fd, int flag)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (!check_option(str[j]) && str[j] != NULL)
		j++;
	if (j > 1)
		with_option(fd, str, j, flag);
	else
		without_option(fd, str, i, flag);
}
