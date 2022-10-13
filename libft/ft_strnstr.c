/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hselbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:48:41 by hselbi            #+#    #+#             */
/*   Updated: 2021/11/23 15:08:27 by hselbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		k;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	str = (char *) haystack;
	if (!*needle)
		return ((char *)haystack);
	while (needle[j] != '\0')
		j++;
	while (str[i] != '\0' && i + j <= len)
	{
		if (ft_strncmp(haystack, needle, j) == 0)
			return ((char *)haystack);
		i++;
		haystack++;
	}
	return (NULL);
}
