/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:12:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/01 11:59:29 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/command.h"
#include "../../include/debug.h"
#include "../../include/minishell.h"
#include "../../include/types.h"

t_token	*get_token(int token_idx, t_data *data)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
	{
		perror("");
		clean_exit_shell(data);
		exit(errno);
	}
	t->token = *(char **)vec_get(&data->cur.tokens, token_idx);
	t->type = *(int *)vec_get(&data->cur.types, token_idx);
	return (t);
}

void	process_normal_mode(int idx, t_token *t, int *args_idx, t_data *data)
{
	cmd_and_args(idx, t->token, args_idx, data);
	data->cur.cmd_list[idx]->args[*args_idx] = NULL;
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
	int		args_index;
	int		mode;
	t_token	*t;

	args_index = 0;
	mode = DEFAULT_MODE;
	while (*token_idx < (int)data->cur.tokens.len && is_delim(*token_idx,
			data) == 0)
	{
		t = get_token(*token_idx, data);
		mode = check_mode(t->token, t->type, cmd_idx, data);
		initialize_cmd_if_needed(cmd_idx, data);
		if (mode != DEFAULT_MODE)
		{
			update_token(token_idx, &t, data);
		}
		else
		{
			process_normal_mode(cmd_idx, t, &args_index, data);
		}
		redirections(cmd_idx, t, &mode, data);
		free(t);
		*token_idx = *token_idx + 1;
	}
}

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
