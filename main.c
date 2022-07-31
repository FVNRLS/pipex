/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 15:18:51 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

void	check_leaks(void)
{
	system("leaks pipex");
}

/*
	Exec the forked child_process.
*/
void	exec_cmd1(char **env, t_pipex *pipex)
{
	int		fd;

	fd = open(pipex->infile, O_RDONLY);
	if (fd < 0 || access(pipex->infile, F_OK) < 0)
		exit_with_error(pipex, INFILE_ERROR);
	dup2(fd, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	close(fd);
	execve(pipex->cmd1_path, pipex->cmd1, env);
}

/*
	Exec the forked parent process.
*/
void	exec_cmd2(char **env, t_pipex *pipex)
{
	int		fd;

	fd = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, PERMISSIONS);
	if (fd < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
	dup2(fd, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	close(fd);
	execve(pipex->cmd2_path, pipex->cmd2, env);

}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int   	status;

	atexit(check_leaks);

	parse_input(argc, argv, env, &pipex);

	if (pipe(pipex.pipe) < 0)
		exit_with_error(&pipex, PIPE_ERROR);
	pipex.pid[0] = fork();
	if (pipex.pid[0] < 0)
		exit_with_error(&pipex, FORK_ERROR);
	else if (pipex.pid[0] == 0)
		exec_cmd1(env, &pipex);
	pipex.pid[1] = fork();
	if (pipex.pid[1] < 0)
		exit_with_error(&pipex, FORK_ERROR);
	else if (pipex.pid[0] == 0)
		exec_cmd2(env, &pipex);
	close_pipes(&pipex);
	waitpid(pipex.pid[0], &status, 0);
	waitpid(pipex.pid[1], &status, 0);
	free_all_alloc_items(&pipex);
	return (0);
}
