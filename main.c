/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/29 19:28:55 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

void	check_leaks(void)
{
	system("leaks pipex");
}


//void	exec_cmd1(char *cmd_path, char **argv, char **env, t_pipex *pipex)
//{
//	int fd;
//
//	fd = dup2(pipex->infile);
//}
//
//void	exec_cmd2(char **cmd, char **argv, char **env, t_pipex *pipex)
//{
//	int fd;
//
//	fd = dup2(pipex->infile);
//}


int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	atexit(check_leaks);
	parse_input(argc, argv, env, &pipex);




	close_pipes(&pipex);
	waitpid(pipex.pid[0], NULL, 0);
	waitpid(pipex.pid[1], NULL, 0);
}
