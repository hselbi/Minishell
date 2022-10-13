/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <hselbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:25:15 by aerrazik          #+#    #+#             */
/*   Updated: 2022/10/11 22:22:14 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<fcntl.h>
# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>

char	*get_next_line(int fd);
char	*ft_strjoinnn(char *s1, char *s2);
int		ft_strchrr(char *s, int c);
char	*ft_strdupl(char *s1);
char	*save(char **all);
char	*helpme(char	**all, char	**buf);

#endif
