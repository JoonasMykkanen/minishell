/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:53:39 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/25 15:29:30 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

void	handle_child(t_pipes *p, t_data *data)
{
	handle_input_redirection_for_execution(p, data);
	handle_output_redirection_for_execution(p, data);
	if (p->idx < data->cur.cmd_count - 1)
	{
		close(p->pipes[p->idx][READ_END]);
		dup2(p->pipes[p->idx][WRITE_END], STDOUT);
	}
	if (p->idx > 0)
	{
		close(p->pipes[p->idx - 1][WRITE_END]);
	}
	execute_cmd(p, p->idx, data);
	exit(0);
}

void	handle_parent(t_pipes *p, t_data *data)
{
	if (p->idx < data->cur.cmd_count - 1)
	{
		close(p->pipes[p->idx][WRITE_END]);
	}
	if (p->idx > 0)
	{
		close(p->pipes[p->idx - 1][READ_END]);
	}
}
