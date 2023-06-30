/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:17:13 by jmykkane          #+#    #+#             */
/*   Updated: 2023/06/30 12:32:12 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int    handle_no_args(t_data *data, int cmd_idx)
{
    if (arr_len(data) < 2)
    {
        return (1);
    }
    cmd_idx -= 1;
    return (0);
}
