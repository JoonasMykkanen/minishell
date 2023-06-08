/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:21:29 by jmykkane          #+#    #+#             */
/*   Updated: 2023/05/30 10:50:40 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_x(va_list *args, int count)
{
	unsigned int	num;
	char			*str;
	int				len;

	num = (unsigned int)va_arg(*args, int);
	str = ft_itoa(num);
	len = ft_hexlen(num);
	ft_puthex_lower_fd(num, 1);
	free(str);
	return (count + len);
}

int	convert_xx(va_list *args, int count)
{
	unsigned int	num;
	char			*str;
	int				len;

	num = (unsigned int)va_arg(*args, int);
	str = ft_itoa(num);
	len = ft_hexlen(num);
	ft_puthex_upper_fd(num, 1);
	free(str);
	return (count + len);
}
