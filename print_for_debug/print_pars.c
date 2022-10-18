#include "../minishell.h"

void    args_pars(t_pars pars)
{
	t_pars  *tmp;
	t_pars  *lst;
	int     i;
	int     ac;

	i = 0;
	ac = 1;
	tmp = &pars;
	lst = &pars;
	while (tmp->args_array)
	{
		ac = 0;
		i = 0;
		while (lst->args_array->args[ac])
			ac++;
		fprintf(stderr, "%d\n", ac);
		while (tmp->args_array->args[i])
		{
			fprintf(stderr, "add %p\n", tmp->args_array->args);
			fprintf(stderr, "add %p\n", tmp->args_array->args[i]);
			if (!i)
				printf("└──%s\n", tmp->args_array->args[i]);
			else if (i + 1 == ac)
				printf("   └── %s]\n", tmp->args_array->args[i]);
			else
				printf("   ├── %s\n", tmp->args_array->args[i]);
			i++;
		}
		printf("%p ==> in\n└──%d\n", &tmp->args_array->fd_input,
			tmp->args_array->fd_input);
		printf("%p ==> out\n└──%d\n", &tmp->args_array->fd_output,
			tmp->args_array->fd_output);
		tmp->args_array = tmp->args_array->next;
	}
}
