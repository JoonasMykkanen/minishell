/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:56:37 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/04 17:55:07 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "../src/libft/libft.h"
# include "ft_types.h"

void	update_prompt(t_data *data);
int		handle_input(char *input, t_data *data);
int		is_multiline(char *input, t_data *data);
char	*handle_heredoc(char **input, t_data *data);
void	handle_multiline(char **input, t_data *data);
int		heredoc_start_index(char *input, t_data *data);
int		get_delim_end_index(char *input, int delim_start_idx);
void	heredoc_free_part_a_and_b(char **part_a, char **part_b);
int		get_delim_start_index(char *input, int heredoc_start_idx);
char	*heredoc_delim(char *input, int heredoc_start_idx, t_data *data);

#endif