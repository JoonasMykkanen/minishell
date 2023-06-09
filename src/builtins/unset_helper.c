/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:58:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/11 21:38:21 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*extract_until_equal(char *arg, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	malloc_error_check(result, data);
	ft_strlcpy(result, arg, i + 1);
	return (result);
}
