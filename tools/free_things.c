#include "../minishell.h"

void	struct_free(t_mcmd *command)
{
	if (command)
	{
		ft_lstclear(&command->en, free);
		ft_lstclear(&command->exp_en, free);
		ft_free(command->spl_str);
		free(command->home);
	}
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	p_free(t_mcmd *command)
{
	int	i;

	printf("args_arr %p \n", command->pars.args_array);
	while (command->pars.args_array)
	{
		i = 0;
		printf("test jad\n");
		printf("1st %p \n", command->pars.args_array->args);
		fprintf(stderr, "1st %p \n", command->pars.args_array->args[0]);
		fprintf(stderr, "2nd %p \n", command->pars.args_array->args[1]);
		while (command->pars.args_array->args[i])
		{
			free(command->pars.args_array->args[i]);
			command->pars.args_array->args[i] = NULL;
			i++;
		}
		free(command->pars.args_array->args);
		command->pars.args_array->args = NULL;
		command->pars.args_array = command->pars.args_array->next;
	}
	free(command->pars.args_array);
	command->pars.args_array = NULL;
}

void	pars_free(t_pars *p)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = p->args_array;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = tmp->next;
		ft_free(p->args_array->args);
		p->args_array = tmp;
	}
}

void	free_two(char **str, int i)
{
	if (i == 0)
	{
		if (str[0])
		{
			free(str[0]);
			str[0] = NULL;
			free(str[1]);
			str[1] = NULL;
			free(str);
			str = NULL;
		}
	}
	else
	{
		if (str[0])
		{
			free(str[0]);
			free(str[1]);
			free(str);
		}
	}
}
