/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:06:59 by aaaraba           #+#    #+#             */
/*   Updated: 2024/03/20 01:18:17 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char const *s1)
{
	size_t	i;
	char	*copy;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	totalsize;
	size_t	i;
	size_t	x;

	x = 0;
	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strjoin("", s2));
	totalsize = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc((sizeof(char) * totalsize + 1));
	if (newstr == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		newstr[i] = s1[i];
		i++;
	}
	while (i < totalsize)
		newstr[i++] = s2[x++];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*src;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	src = (char *)malloc(len + 1);
	if (src == NULL)
		return (NULL);
	while (i < len)
	{
		src[i] = s[start + i];
		i++;
	}
	src[i] = '\0';
	return (src);
}
