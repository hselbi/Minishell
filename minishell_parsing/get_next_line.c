/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:24:42 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/11 22:22:20 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"
#include"get_next_line.h"

char	*save(char **all)
{
	char	*holder;
	int		i;
	int		j;

	if (!(*all)[0])
		return (0);
	j = 0;
	while ((*all)[j] && (*all)[j] != '\n')
		j++;
	holder = (char *)malloc(ft_strleng(*all) - j + 2);
	if (!holder)
		return (NULL);
	i = 0;
	if ((*all)[j++] == '\n' && (*all)[j] != '\0')
	{
		while ((*all)[j])
			holder[i++] = (*all)[j++];
		holder[i] = '\0';
		free (*all);
		return (holder);
	}
	free(*all);
	free(holder);
	return (0);
}

char	*helpme(char	**all, char	**buf)
{
	char	*ret;

	if (all && ft_strchrr(*all, '\n') != 1 && !ft_strleng(*all))
	{
		free(all);
		free(buf);
		return (0);
	}
	ret = ft_strdupl(*all);
	*all = save(all);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*all;
	char		*buf;
	int			len;

	if (fd < 0 || 4 <= 0)
		return (0);
	buf = malloc(sizeof(char) * 1 + 1);
	if (!buf)
		return (0);
	len = 1;
	while (len > 0 && ft_strchrr(all, '\n') != 1)
	{
		len = read(fd, buf, 1);
		buf[len] = '\0';
		if (len <= 0 && !ft_strleng(all))
		{
			free(buf);
			return (NULL);
		}
		all = ft_strjoinnn(all, buf);
	}
	free(buf);
	return (helpme(&all, &buf));
}
