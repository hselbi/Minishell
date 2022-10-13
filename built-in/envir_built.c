#include "../minishell.h"

/******************************************************
	 this is one is when in the first time
******************************************************/

t_list	*ft_env(char **en)
{
	t_list	*tmp_en;
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (en[len])
		len++;
	str = ft_strdup(en[i]);
	tmp_en = ft_lstnew(str);
	i++;
	while (i < len)
	{
		str = ft_strdup(en[i]);
		ft_lstadd_back(&tmp_en, ft_lstnew(str));
		i++;
	}
	return (tmp_en);
}
/******************************************************
	this only work for if i put export command
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
