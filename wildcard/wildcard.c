#include "../minishell.h"

char	*free_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	free((void*)s2);
	return (str);
}

// void	add_arg(char *str, char *tmp)
// {
// 	t_wild	*new;
// 	char	*word;

// 	tmp += 2;
// 	word = ft_strdup(tmp);
// 	new = create_wild(word, 1);
// 	free(word);
// 	new->prev = arg;
// 	new->next = arg->next;
//     if (new->next)
//         new->next->prev = new;
//     else   
//         new->next = NULL;
// 	// new->next ? new->next->prev = new : 0;
// 	arg->next = new;
// 	arg->type = 11;
// }

void    wild_on(char *str, char *s, int i, char **sp)
{
    DIR             *dir;
    struct dirent   *d;
    char            *tmp;
    int             slash;

    i = 0;
    slash = s_count(s);
    i += ft_strlen(s) - 1;
    dir = opendir(s);
    while (str[i] && str[i] != '/')
        i++;
    while (sp[slash] && (d = readdir(dir)))
    {
        tmp = ft_strjoin("/", d->d_name);
        tmp = free_strjoin(s, tmp);
        /*
        * is not null
        ^ 
        */
        if ((!str[i] || !str[i + 1]) && str_match(sp[slash], d->d_name, 0, 0) && (is_strequ(d->d_name, sp[slash]) || d->d_name[0] != '.' || sp[slash][0] == '.'))
        {
            // add_arg(str, tmp);
        }
        else if (str_match(sp[slash], d->d_name, 0, 0) && (is_strequ(d->d_name, sp[slash]) || d->d_name[0] != '.' || sp[slash][0] == '.'))
            wild_on(str, s, i + 1, sp);
        free(tmp);
    }
    dir ? closedir(dir) : 0;
}

void    wild_take(char *str)
{
    // t_wild  *w;
    char    **sp;
    char    *s;
    
    sp = ft_split(str, '/');
    s = wild_path(str);
    printf("sp: %s\n", sp[0]);
    printf("s: %s\n", s);
    wild_on(str, s, 0, sp);
    //free sp
    // free s
}

void    init_wild(t_pars *array_args)
{
    t_pars  *tmp;
    int i;

    tmp = array_args;
    while(tmp)
    {
        i = 1;
        while (tmp->args[i])
        {
            if(is_asterisk('*', tmp->args[i]) > -1)
                wild_take(tmp->args[i]);
            i++;
        }
        tmp = tmp->next;
    }
}