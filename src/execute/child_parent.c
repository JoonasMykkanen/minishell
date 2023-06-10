/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:53:39 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/10 20:11:42 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execute.h"

extern t_data	g_data;

// Works in vscdode
// void handle_child(t_pipes *p)
// {
//     handle_input_redirection_for_execution(p);
//     handle_output_redirection_for_execution(p);
//     if (p->idx < g_data.cur.cmd_count - 1)
// 	{
//         close(p->pipes[p->idx][READ_END]);
// 	}
//     if (p->idx < g_data.cur.cmd_count - 1)
// 	{
//         dup2(p->pipes[p->idx][WRITE_END], STDOUT);
// 	}
//     execute_cmd(p, p->idx);
// }
void handle_child(t_pipes *p)
{
    handle_input_redirection_for_execution(p);
    handle_output_redirection_for_execution(p);

    // If not the last command, redirect STDOUT to write end of the current pipe
    if (p->idx < g_data.cur.cmd_count - 1)
    {
        close(p->pipes[p->idx][READ_END]);
        dup2(p->pipes[p->idx][WRITE_END], STDOUT);
    }

    if (p->idx > 0)
    {
        close(p->pipes[p->idx - 1][WRITE_END]); // Close unused write end of previous pipe
    }

    execute_cmd(p, p->idx);
    exit(0); // Child process should terminate after executing command
}

// Works in vscode
// void handle_parent(t_pipes *p)
// {
//     if (p->idx < g_data.cur.cmd_count - 1)
// 	{
//         close(p->pipes[p->idx][WRITE_END]);
// 	}
//     if (p->idx > 0)
// 	{
//         close(p->pipes[p->idx - 1][READ_END]);
// 	}
// }

void handle_parent(t_pipes *p)
{
    if (p->idx < g_data.cur.cmd_count - 1)
    {
        close(p->pipes[p->idx][WRITE_END]); // Parent does not write to current pipe
    }

    if (p->idx > 0)
    {
        close(p->pipes[p->idx - 1][READ_END]); // Parent done reading from previous pipe
    }
}