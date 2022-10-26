/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:54:33 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/25 22:54:34 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************************************************************
*		*	table(with extra ' ') of files in current directory		*						  
***************************************************************************/

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

/**************************************************************************
*		*          size of files in current directory		      *					  
***************************************************************************/

int	size_dir(void)
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

/**************************************************************************
*		*          characters that are before asterisk		      *					  
***************************************************************************/

char	*prefix(char *str)
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

/**************************************************************************
*		*         characters that are after asterisk		      *					  
***************************************************************************/

char	*suffix(char *str)
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
	res[j] = '\0';
	return (res);
}

/**************************************************************************
*	*         check string is match with suffix characters		      *					  
***************************************************************************/

int	suffix_check(char *str, char *su)
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
