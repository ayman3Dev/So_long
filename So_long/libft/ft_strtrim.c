/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:13:03 by aaaraba           #+#    #+#             */
/*   Updated: 2023/11/15 12:14:41 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		sizes1;
	char	*newstr;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	sizes1 = ft_strlen(s1);
	while (i < sizes1 && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (i < sizes1 && ft_strrchr(set, s1[sizes1 - 1]) != NULL)
	{
		sizes1--;
	}
	newstr = (char *)malloc (sizeof(char) * ((sizes1 - i) + 1));
	if (newstr == NULL)
		return (NULL);
	j = 0;
	while (i < sizes1)
	{
		newstr[j++] = s1[i++];
	}
	newstr[j] = '\0';
	return (newstr);
}
