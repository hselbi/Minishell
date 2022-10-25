/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:49:14 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/24 22:33:39 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i <= (int)ft_strleng(s))
	{
		if (i > 0 && s[i - 1] != c && (s[i] == c || s[i] == '\0'))
			count++;
		while (s[i] == c)
			i++;
		if (i <= (int)ft_strleng(s))
			i++;
	}
	return (count);
}

char	*sp(const char *s, int e, int b)
{
	int		i;
	char	*sp;

	sp = (char *)malloc(sizeof(char) * (e - b + 1));
	if (!sp)
		return (NULL);
		i = 0;
	while (b < e)
	{
		sp[i] = s[b];
		i++;
		b++;
	}
	sp[i] = '\0';
	return (sp);
}

char	**ft_split_with_pipe(char *s, char c, t_pars *pars)
{
	t_sp	splt;

	if (!s)
		return (NULL);
	splt.spl = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!splt.spl)
		return (NULL);
	splt_init(&splt);
	while (++splt.i <= (int)ft_strleng(s))
	{
		if (s[splt.i] != c && s[splt.i] && splt.b == -1)
			splt.b = splt.i;
		if ((s[splt.i] == c || s[splt.i] == '\0') && splt.b >= 0)
		{
			splt.spl[splt.j++] = sp(s, splt.i, splt.b);
			splt.b = -1;
			if (s[splt.i] && s[splt.i +1] == c)
			{
				error_exit("Error multiple consecutive pipes !\n", pars);
				break ;
			}
		}
	}
	splt.spl[splt.j] = 0;
	return (splt.spl);
}

void	splt_init(t_sp *splt)
{
	splt->i = -1;
	splt->j = 0;
	splt->b = -1;
}

char	**ft_spliti(char *s, char c)
{
	char	**spl;
	int		i;
	int		j;
	int		b;

	if (!s)
		return (NULL);
	spl = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!spl)
		return (NULL);
	i = -1;
	j = 0;
	b = -1;
	while (++i <= (int)ft_strleng(s))
	{
		if (s[i] != c && s[i] && b == -1)
			b = i;
		if ((s[i] == c || s[i] == '\0') && b >= 0)
		{
			spl[j++] = sp(s, i, b);
			b = -1;
		}
	}
	spl[j] = 0;
	return (spl);
}
