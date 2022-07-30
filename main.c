/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/30 16:39:35 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

void	check_leaks(void)
{
	system("leaks pipex");
}

void	exec_cmd1(char **argv, char **env, t_pipex *pipex)
{
	int		fd;

	fd = check_open_infile(pipex->infile);
	dup2(fd, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close_pipes(pipex);
	close(fd);
	if (execve(pipex->cmd1_path, argv, env) < 0)
		exit_with_error("Error. Unknown first command.\n", EXECVE_ERROR);
}

void	exec_cmd2(char **argv, char **env, t_pipex *pipex)
{
	int		fd;

	fd = check_open_outfile(pipex->outfile);
	dup2(fd, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close_pipes(pipex);
	close(fd);
	if (execve(pipex->cmd2_path, argv, env) < 0)
		exit_with_error("Error. Unknown second command.\n", EXECVE_ERROR);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

//	atexit(check_leaks);

	parse_input(argc, argv, env, &pipex);

	if (pipe(pipex.pipe) < 0)
		exit_with_error("Error. Problems with pipe redirection.\n", PIPE_ERROR);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		exit_with_error("Error. No child process created.", FORK_ERROR);
	else if (pipex.pid[0] == 0)
		exec_cmd1(argv, env, &pipex);
	if (pipex.pid[1] < 0)
		exit_with_error("Error. No child process created.", FORK_ERROR);
	else if (pipex.pid[1] == 0)
		exec_cmd2(argv, env, &pipex);

	close_pipes(&pipex);
	waitpid(pipex.pid[0], NULL, 0);
	waitpid(pipex.pid[1], NULL, 0);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
}
