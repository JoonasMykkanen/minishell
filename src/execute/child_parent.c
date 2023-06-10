/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:53:39 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/10 12:12:23 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

void handle_child(t_pipes *p)
{
    handle_input_redirection_for_execution(p);
    handle_output_redirection_for_execution(p);

    // Close the read end of the current pipe in child
    if (p->idx < g_data.cur.cmd_count - 1)
        close(p->pipes[p->idx][READ_END]);

    // For the commands other than the last, connect STDOUT to the write end of the pipe
    if (p->idx < g_data.cur.cmd_count - 1)
        dup2(p->pipes[p->idx][WRITE_END], STDOUT_FILENO);

    execute_cmd(p, p->idx);
}


void handle_parent(t_pipes *p)
{
    // Close the write end of the current pipe in parent
    if (p->idx < g_data.cur.cmd_count - 1)
        close(p->pipes[p->idx][WRITE_END]);

    // Close the read end of the previous pipe (except for the first command)
    if (p->idx > 0)
        close(p->pipes[p->idx - 1][READ_END]);

    // wait(NULL); // You may want to modify this to handle errors
}
