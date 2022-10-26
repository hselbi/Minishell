/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:54:38 by hselbi            #+#    #+#             */
/*   Updated: 2022/10/25 22:54:39 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************************************************************
*	* check prefix and suffix is match with every file in current dir *
***************************************************************************/

char	*wc_parser(char *str, int i, char *out, char **arr)
{
	char	*suf;
	char	*pref;

	arr = files_tab(i);
	if (!str || i == 0 || !arr)
		return (NULL);
	pref = prefix(str);
	suf = suffix(str);
	out = ft_strdup("");
	i = 0;
	while (arr[i])
	{
		if (!pref && !suf)
			out = strjoin_free(out, arr[i]);
		else if (pref && !ft_strncmp(pref, arr[i] + 1, ft_strlen(pref)) && !suf)
			out = strjoin_free(out, arr[i]);
		else if (suf && !pref && suffix_check(arr[i], suf))
			out = strjoin_free(out, arr[i]);
		else if (suffix_check(arr[i], suf)
			&& !ft_strncmp(pref, arr[i] + 1, ft_strlen(pref)))
			out = strjoin_free(out, arr[i]);
		i++;
	}
	free_ast(pref, suf, arr);
	return (out);
}

/**************************************************************************
*			*          return the starting point		      *	
***************************************************************************/

int	start_finder(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] == ' ')
			return (i + 1);
		i--;
	}
	return (0);
}
/**************************************************************************
*			*          return the terminating point		      *	
***************************************************************************/

int	finish_finder(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

/**************************************************************************
*				*		main function of wildcard		*	
***************************************************************************/

char	*ast_replace(char *line, int i)
{
	int			beg;
	int			end;
	static char	*ast;
	static char	*put_back;

	beg = start_finder(line, i);
	end = finish_finder(line, i);
	ast = ft_substr(line, beg, end - beg);
	if (!ast)
		return (line);
	put_back = wc_parser(ast, size_dir(), NULL, NULL);
	if (!put_back)
		return (line);
	put_back = strjoin_free(put_back, line + end);
	line[beg] = '\0';
	line = strjoin_free(line, put_back);
	free(put_back);
	free(ast);
	return (line);
}

/**************************************************************************
*				*		check if there's asterik		*	
***************************************************************************/

char	*wc_handle(char *line)
{
	int	i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) == '*')
		{
			line = ast_replace(line, i);
			i++;
		}
		else
			i++;
	}
	return (line);
}
