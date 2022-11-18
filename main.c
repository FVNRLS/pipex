/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

/*
	Gathers the names and command paths from the arguments.
 	Executes the commands, passing the content of infile as input to the outfile
 	via pipe.
*/
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	parse_input(argc, argv, env, &pipex);
	pipe_input(env, &pipex);
	return (0);
}
