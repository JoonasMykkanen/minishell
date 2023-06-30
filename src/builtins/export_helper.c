/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:17:13 by jmykkane          #+#    #+#             */
/*   Updated: 2023/06/30 13:27:07 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int    handle_no_args(t_data *data)
{
    if (arr_len(data) < 2)
    {
        printf("Shell: Export: No arguments given\n");
		return (1);
    }
    return (0);
}
