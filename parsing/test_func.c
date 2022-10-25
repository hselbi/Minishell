/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:37:55 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/25 20:35:31 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include"parser.h"

/*****************************************************************************/
/* ft_isalnum to check if the argument after dollar sign could be expanded   */
/* or not																	 */
/*****************************************************************************/

int	ft_isalnum_dyali(char str)
{
	if ((str >= 'a' && str <= 'z')
		|| (str >= 'A' && str <= 'Z')
		|| (str >= '0' && str <= '9'))
		return (0);
	else
		return (1);
}

/*****************************************************************************/
/* make_word a tool making strings											 */
/*****************************************************************************/

char	*make_word(char *sentance, int begin, int end)
{
	int		size;
	char	*new_word;
	int		i;

	size = end - begin + 1;
	if (!sentance || size <= 0)
		return (NULL);
	new_word = (char *)malloc(sizeof(char) * size + 1);
	if (!new_word)
		return (NULL);
	i = 0;
	while (i < size)
		new_word[i++] = sentance[begin++];
	new_word[i] = '\0';
	return (new_word);
}

/*****************************************************************************/
/* others take normal characters and make arguments from them and split with */
/* space that it should bein splited with not thoses in quotes				 */
/*****************************************************************************/

void	others(char *commands, t_pars *pars)
{
	char	*new;
	int		len;

	len = 2;
	if (pars->i > 0 && (commands[pars->i] == '<'
			|| (commands[pars->i] == '>' && commands[pars->i -1] != '>')))
		len = 3;
	new = (char *)malloc(sizeof(char) * len);
	if (!new)
		return ;
	if (pars->i > 0 && (commands[pars->i] == '<'
			|| (commands[pars->i] == '>' && commands[pars->i -1] != '>')))
	{
		new[0] = '	';
		new[1] = commands[pars->i];
	}
	else
	{
		new[0] = commands[pars->i];
		if (new[0] == ' ')
			new[0] = '	';
	}
	new[len - 1] = '\0';
	pars->i++;
	pars->for_struct = ft_strjoinn(pars->for_struct, new);
}

/*****************************************************************************/
/* make_struct is the main function to pars the string into different struct */
/* 1- cmd  : a command to execute											 */
/* 2- args : the arguments that follows cmd	ended by NULL					 */
/* 3- here_doc_limiter : if there is a here_doc it takes his limiter 		 */
/* 4- infile  : takes the name of the file redirected to as input			 */
/* 5- outfile : takes the name of the file redirected to as output			 */
/*****************************************************************************/

void	make_struct(char *commands, t_pars	*pars)
{
	pars->i = 0;
	pars->file = NULL;
	pars->for_struct = NULL;
	pars->hold_input = STDIN_FILENO;
	pars->hold_output = STDOUT_FILENO;
	while (commands[pars->i])
	{
		if (commands[pars->i] == '"')
			take_word(commands, pars, pars->i + 1);
		else if (commands[pars->i] == '\'')
			take_word_2(commands, pars, pars->i + 1);
		else if (commands[pars->i] == '<' && commands[pars->i + 1] == '<')
			for_here_doc(commands, pars);
		else if (commands[pars->i] == '\\' && commands[pars->i +1] == '$')
			pars->i++;
		else if (commands[pars->i] == '$' && commands[pars->i -1] != '\\')
			check_valid_dollar(commands, pars);
		else
			others(commands, pars);
	}
	free(commands);
	pars->error = 0;
	pars->index = 0;
	make_struct_to_execute(pars);
}

/*****************************************************************************/
/* It exit when it's ERROR													 */
/*****************************************************************************/

void	error_exit(char *str, t_pars *pars)
{
	int	i;

	i = 0;
	perror(str);
	pars->error = 5;
	if (pars->args_array != NULL)
	{
		while (pars->args_array->args[i])
			free(pars->args_array->args[i++]);
		free(pars->args_array);
		pars->args_array = NULL;
	}
}
