/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:02:38 by kbagot            #+#    #+#             */
/*   Updated: 2016/11/14 12:29:44 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int			i;
	char		*d;
	const char	*s;

	i = 0;
	d = (char*)dest;
	s = (const char*)src;
	if (s < d)
	{
		s = s + n - 1;
		d = d + n - 1;
		while (n > 0)
		{
			*d-- = *s--;
			n--;
		}
	}
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}
