/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	If number of arguments less than 4 -> exit.
 	Otherwise:
 		1) create input/heredoc and output file
 		2) parse, pipe and execute the commands.
	Exit with error message, if any action goes wrong.
 	(see /src/bonus/error_manager_bonus.c).
*/
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	t_args	args;

	pipex.args = &args;
	args.argc = argc;
	args.argv = argv;
	if (argc < 5)
		exit_with_error(&pipex, ARGNUM_ERROR);
	parse_exec_input(env, &pipex);
	return (0);
}
