/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:43:16 by aaaraba           #+#    #+#             */
/*   Updated: 2023/11/22 11:22:58 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	of;

	of = count * size;
	if (count != 0 && of / count != size)
		return (NULL);
	p = malloc (count * size);
	if (p == 0)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}
