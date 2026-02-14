/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:14:55 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/14 13:14:31 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmd
{
	char	**argv;
	char	*input_file;
	char	*output_file;
	int		append_output;
	int		is_builtin;
	char	**hd_delim;
	int		hd_expand;
	int		hd_count;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	**cmds;
	int		cmd_count;
	char	**envp;
	int		last_status;
}	t_shell;

#endif
