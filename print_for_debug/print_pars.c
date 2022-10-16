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
		while (tmp->args_array->args[i])
		{
			if (!i)
			{
				printf("%p ==> ", tmp->args_array->args[i]);
				printf("└──%s\n", tmp->args_array->args[i]);
			}
			else if (i + 1 == ac)
				printf("   └── %s\n", tmp->args_array->args[i]);
			else
				printf("   ├── %s\n", tmp->args_array->args[i]);
			i++;
		}
		// char pathbuf[1024];
		printf("%p ==> in\n└──%d\n", &tmp->args_array->fd_input,
			tmp->args_array->fd_input);
		printf("%p ==> out\n└──%d\n", &tmp->args_array->fd_output,
			tmp->args_array->fd_output);
		// if (fcntl(tmp->args_array->fd_input, F_GETPATH, pathbuf) >= 0)
		// 	printf("in path %s\n", pathbuf);
		// if (fcntl(tmp->args_array->fd_output, F_GETPATH, pathbuf) >= 0)
		// 	printf("out path %s\n", pathbuf);
		tmp->args_array = tmp->args_array->next;
	}
}

void	ft_print_pars(t_pars *pars)
{
	fprintf(stderr, "%p => pars->args_array\n", pars->args_array);
	fprintf(stderr, "%d => pars->check\n", pars->check);
	fprintf(stderr, "%p => pars->command\n", pars->command);
	fprintf(stderr, "%p => pars->env\n", pars->env);
	fprintf(stderr, "%d => pars->fd_input\n", pars->fd_input);
	fprintf(stderr, "%d => pars->fd_output\n", pars->fd_output);
	fprintf(stderr, "%p => pars->for_struct\n", pars->for_struct);
	fprintf(stderr, "%p => pars->here_doc_limiter\n", pars->here_doc_limiter);
	fprintf(stderr, "%d => pars->i\n", pars->i);
	fprintf(stderr, "%d => pars->index\n", pars->index);
	fprintf(stderr, "%p => pars->infile\n", pars->infile);
	fprintf(stderr, "%p => pars->next\n", pars->next);
	fprintf(stderr, "%d => pars->node_nmb\n", pars->nodes_nmb);
	fprintf(stderr, "%p => pars->outfile\n", pars->outfile);
}
