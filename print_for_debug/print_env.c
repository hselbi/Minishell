#include "../minishell.h"

void	exp_envp(t_list *list, int fd, int flag)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (!tmp->content)
			tmp = tmp->next;
		if (flag == 1)
		{
			write(fd, tmp->content, ft_strlen(tmp->content));
			write(fd, "\n", 1);
		}
		else
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
