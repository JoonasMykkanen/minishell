/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:52:33 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/11 13:46:23 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	redir_input(t_pipes *p, t_data *data)
{
	p->fdin = open(data->cur.cmd_list[p->idx]->input, O_RDONLY);
	if (p->fdin < 0)
	{
		perror("input file");
		clean_exit_shell(data, PARENT);
		exit(1);
	}
}

void	redir_out(t_pipes *p, t_data *data)
{
	if (data->cur.cmd_list[p->idx]->output_mode == APPEND_MODE)
		p->fdout = open(data->cur.cmd_list[p->idx]->output,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (data->cur.cmd_list[p->idx]->output_mode == OVERWRITE_MODE)
	{
		p->fdout = open(data->cur.cmd_list[p->idx]->output,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		perror("invalid output mode");
		clean_exit_shell(data, PARENT);
		exit(1);
	}
	if (p->fdout < 0)
	{
		perror("output file");
		clean_exit_shell(data, PARENT);
		exit(1);
	}
}

void	handle_input_redirection_for_execution(t_pipes *p, t_data *data)
{
	if (data->cur.cmd_list[p->idx]->input == NULL)
	{
		if (p->idx == 0)
			p->fdin = STDIN_FILENO;
		else
			p->fdin = p->pipes[p->idx - 1][READ_END];
	}
	else
	{
		redir_input(p, data);
	}
	dup2(p->fdin, STDIN_FILENO);
	if (p->fdin != STDIN_FILENO)
		close(p->fdin);
}

void	handle_output_redirection_for_execution(t_pipes *p, t_data *data)
{
	p->out_redirected = FALSE;
	if (data->cur.cmd_list[p->idx]->output == NULL)
	{
		p->fdout = STDOUT;
	}
	else
	{
		redir_out(p, data);
		p->out_redirected = TRUE;
	}
	if (p->fdout != STDOUT)
	{
		dup2(p->fdout, STDOUT);
		close(p->fdout);
	}
}
