/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 07:53:13 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/07/03 17:35:01 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_EXIT_H
# define CLEAN_EXIT_H

void	free_arr(char **arr);
void	clean_exit_shell(t_data *data, int caller);

#endif