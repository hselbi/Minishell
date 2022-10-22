#include "../minishell.h"

/******************************************************
*		* this is one is when in the first time *
******************************************************/

t_list	*ft_env(char **en)
{
	t_list	*tmp_en;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (en[len])
		len++;
	while (i < len)
	{
		if (!i)
			tmp_en = ft_lstnew(en[i]);
		else
			ft_lstadd_back(&tmp_en, ft_lstnew(en[i]));
		i++;
	}
	return (tmp_en);
}
/******************************************************
*	* this only work for if i put export command *
******************************************************/

void	my_env(t_mcmd *command)
{
	if (ft_strlen(command->av[0]) != 3)
		printf("%s: command not found\n", command->av[0]);
	else
	{
		printf("%s: No such file or directory\n", command->av[0]);
		g_status = 1;
	}
}

/******************************************************
*	* this only work for if i put export command *
******************************************************/

void	exp_envp(t_list *list, int fd, int flag)
{
	t_list	*tmp;

	tmp = list;
	printf("*********** head  ==> %p\n", &list);
	printf("***********  ==> %p\n", list);
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
