/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:28:08 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/28 12:28:09 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	ch;
	unsigned char	*src;

	i = 0;
	ch = c;
	src = (unsigned char *)s;
	while (n > 0)
	{
		if (*((unsigned char *)s + i) == ch)
		{
			return (&src[i]);
		}
		n--;
		i++;
	}
	return (NULL);
}
