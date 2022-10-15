/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 09:01:59 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/11 22:21:05 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

/*****************************************************************************/
/* To check when the quotes are open or closed								 */
/*****************************************************************************/

void	check_open_quote2(char *sp, t_pars *pars)
{
	if (sp[pars->i] == '"' && pars->check == 0)
	{
		pars->check = D_COTE;
		pars->i++;
	}
	else if (sp[pars->i] == '\'' && pars->check == 0)
	{
		pars->check = COTE;
		pars->i++;
	}
	else if (sp[pars->i] == '"' && pars->check == D_COTE)
	{
		pars->check = 0;
		pars->i++;
	}
	else if (sp[pars->i] == '\'' && pars->check == COTE)
	{
		pars->check = 0;
		pars->i++;
	}
}

char	*space(char *str)
{
	int		i;
	char	*to_ret;

	i = 0;
	to_ret = (char *)malloc(sizeof(char) * 4);
	if (!to_ret)
		return (NULL);
	while (str[i])
	{
		to_ret[i] = str[i];
		i++;
	}
	to_ret[i] = '\0';
	return (to_ret);
}

/*****************************************************************************/
/* take_word returns the argument inside doube_quotes and if there is a 	 */
/* dollar sign it check and expand it										 */
/*****************************************************************************/

void	take_word(char *commands, t_pars *pars, int i)
{
	int		j;
	char	*word;

	j = 0;
	if (commands[i] == '"')
	{
		pars->i++;
		pars->i++;
		pars->for_struct = ft_strjoinn(pars->for_struct, space(" "));
	}
	else
	{
		while (commands[i] && commands[i++] != '"')
			j++;
		word = (char *)malloc(sizeof(char) * (j + 1));
		if (!word)
			return ;
		j = 0;
		while (commands[++pars->i] && commands[pars->i] != '"')
			word[j++] = commands[pars->i];
		pars->i++;
		word[j] = '\0';
		word = check_dollar(word, pars);
		pars->for_struct = ft_strjoinn(pars->for_struct, word);
	}
}

/*****************************************************************************/
/* take_word_2 returns the argument inside quotes							 */
/*****************************************************************************/

void	take_word_2(char *commands, t_pars *pars, int i)
{
	int		j;
	char	*word;

	j = 0;
	if (commands[i] == '\'')
	{
		pars->i++;
		pars->i++;
		pars->for_struct = ft_strjoinn(pars->for_struct, space(" "));
		return ;
	}
	while (commands[i] && commands[i++] != '\'')
		j++;
	word = (char *)malloc(sizeof(char) * (j + 1));
	if (!word)
		return ;
	j = 0;
	while (commands[++pars->i] && commands[pars->i] != '\'')
		word[j++] = commands[pars->i];
	pars->i++;
	word[j] = '\0';
		pars->for_struct = ft_strjoinn(pars->for_struct, word);
}
