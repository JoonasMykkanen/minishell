/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:01 by oanttoor          #+#    #+#             */
/*   Updated: 2023/06/25 15:34:39 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/minishell.h"
#include "../../include/debug.h"

/* 
	Parse input takes in a perfect list of tokens and creates 
	perfect command structs that can be passed to execute 
*/
int	parse_commands(t_data *data)
{
	int	cmd_idx;
	int	token_idx;

	cmd_idx = 0;
	token_idx = 0;
	get_cmd_count(data);
	allocate_cmd_list(data);
	while (cmd_idx < data->cur.cmd_count)
	{
		parse_single_cmd(cmd_idx, &token_idx, data);
		token_idx++;
		cmd_idx++;
	}
	return (0);
}

// get_token should return the entire token
t_token	*get_token(int token_idx, t_data *data)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
	{
		perror("");
		clean_exit_shell(data);
		exit (errno);
	}
	t->token = *(char **)vec_get(&data->cur.tokens, token_idx);
	t->type = *(int *)vec_get(&data->cur.types, token_idx);
	return (t);
}

void	update_token(int *token_idx, t_token **t, t_data *data)
{
	*token_idx = *token_idx + 1;
	if (*token_idx < (int)data->cur.tokens.len)
	{
		*t = get_token(*token_idx, data);
	}
}

void	parse_single_cmd(int cmd_idx, int *token_idx, t_data *data)
{
	int			args_index;
	int			mode;
	t_token		*t;

	args_index = 0;
	mode = DEFAULT_MODE;
	while (*token_idx < (int)data->cur.tokens.len && is_delim(*token_idx, data) == 0)
	{
		t = get_token(*token_idx, data);
		mode = check_mode(t->token, t->type, cmd_idx, data);
		if (mode != DEFAULT_MODE)
			update_token(token_idx, &t, data);
		else
			handle_cmd_and_args(cmd_idx, t->token, &args_index, data);
		if (mode == INPUT_REDIR)
			handle_input_redirection(cmd_idx, t->token, &mode, data);
		else if (mode == OUTPUT_REDIR_APPEND || mode == OUTPUT_REDIR_OVERWRITE)
			handle_output_redirection(cmd_idx, t->token, &mode, data);
		*token_idx = *token_idx + 1;
		data->cur.cmd_list[cmd_idx]->args[args_index] = NULL;
		free(t);
	}
}
