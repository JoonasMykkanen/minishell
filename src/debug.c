/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:05:30 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/06/15 17:08:20 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/debug.h"

extern	t_data	g_data;

// All functions in this file are only meant to be debugged with
// they are not in use at all when this project is submitted but
// I felt it is important to preserve the way how this shell was
// developed. That is why This file is left here and functions can
// be taken into use anywhere if needed. :-)
// There was also unit tests when project started but they were
// doomed too much effort to keep making for each functions as
// project scope increased over time.
void	debug_print_list(char	**list, const char *func_name)
{
	printf("Debugging list in function %s:\n", func_name);
	for (int i = 0; list[i] != NULL; i++)
	{
		printf("%d: %s	\n", i, list[i]);
	}
	printf("Finished printing list.\n");
}

void	print_list(char	**list)
{
	for (int i = 0; list[i] != NULL; i++)
	{
		ft_printf("%s;", list[i]);
	}
}

void	debug_print_string(char *string, const char *func_name)
{
	printf("Debugging string in function %s:\n", func_name);
	printf("string: %s\n", string);
}

void debug_print_tokens()
{
  ft_printf("\n\n----- TOKENIZE OUTPUT SUMMARY -----\n\n");
  ft_printf("number of tokens: %d\n",g_data.cur.tokens.len);
  for (size_t i = 0; i < g_data.cur.tokens.len; i++) {
    char *token = *(char **)vec_get(&g_data.cur.tokens, i);
    int *type = vec_get(&g_data.cur.types, i);
    ft_printf("Token %d: \n Content: **%s**\n Type: %d\n", i, token, *type);
  }
  ft_printf("\n----- END OF TOKENIZE OUTPUT -----\n\n");
}

void  debug_print_commands()
{
	ft_printf("\n\n----- PARSER OUTPUT SUMMARY -----\n\n");
	ft_printf("number of commands: %d\n",g_data.cur.cmd_count);

	for (int i = 0; i < g_data.cur.cmd_count; i++) {
	t_cmd *cmd = g_data.cur.cmd_list[i];
	ft_printf("\nCommand %d: \n Cmd: %s\n", i, cmd->cmd);
	ft_printf(" Args: ");
	if (cmd->args) {
		print_list(cmd->args);
		ft_printf("\n");
	} else {
		ft_printf("no arguments\n");
	}
	if (cmd->input) {
		ft_printf(" Input: %s\n", cmd->input);
	}
	if (cmd->output) {
		ft_printf(" Output: %s\n", cmd->output);
	}
	if (cmd->output_mode) {
		ft_printf(" Output mode: %d\n", cmd->output_mode);
	}
	}
	ft_printf("\n----- END OF PARSER OUTPUT -----\n\n");
}