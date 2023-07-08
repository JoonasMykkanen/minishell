/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:26:35 by oanttoor          #+#    #+#             */
/*   Updated: 2023/07/07 13:53:23 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "bonus.h"

extern int	g_sig_status;

static void	welcome_message(void)
{
	printf("Welcome to school 42 minishell bonus part \n");
	printf("here I have fooled around and created anything that\n");
	printf("popped in my mind. Most notably, changed curor to emojis...\n");
	printf("that was not an easy task, it required rewriting readline()\n");
}

static void	execute_loop(char *input, t_data *data)
{
	if (ft_strlen(input) != 0)
	{
		if ((input && *input) && g_sig_status != SIG_ERROR)
			add_history(input);
		if (g_sig_status != SIG_ERROR)
			handle_input(input, data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			tokenize_input(data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			parse_commands(data);
		if (data->cur.err_flag == 0 && g_sig_status != SIG_ERROR)
			execute(data);
	}
	else if (input == NULL)
		handle_ctrl_d(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	if (argc != 1 && argv[1] != NULL)
		return (1);
	welcome_message();
	signal_manager();
	termios_settings(YES);
	if (init_struct(envp, &data) == 1)
		perror("init_struct");
	while (42)
	{
		input = ft_readline(data.env.prompt);
		execute_loop(input, &data);
		clean_cur_struct(&data);
		update_prompt(&data);
	}
	clean_exit_shell(&data, PARENT);
	return (data.env.exit_status);
}
