/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 16:04:11 by rmazurit         ###   ########.fr       */
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
