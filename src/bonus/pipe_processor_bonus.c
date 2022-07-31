/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:18:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 17:54:55 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

static void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

/*
	Exec the forked child_process.
*/
static void	exec_cmd1(char **env, t_pipex *pipex)
{
	dup2(fd, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	close(fd);
	if (execve(pipex->cmd1_path, pipex->cmd1, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

/*
	Exec the forked parent process.
*/
static void	exec_cmd2(char **env, t_pipex *pipex)
{
	int		fd;

	dup2(fd, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	close(fd);
	if (execve(pipex->cmd2_path, pipex->cmd2, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

void	pipe_input(char **env, t_pipex *pipex)
{
	int   	status;

	if (pipe(pipex->pipe) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		exit_with_error(pipex, FORK_ERROR);
	else if (pipex->pid[0] == 0)
		exec_cmd1(env, pipex);
	waitpid(pipex->pid[0], &status, 0);
	if (status != 0)
		exit(EXIT_FAILURE);
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
		exit_with_error(pipex, FORK_ERROR);
	else if (pipex->pid[1] == 0)
		exec_cmd2(env, pipex);
	close_pipes(pipex);
	waitpid(pipex->pid[1], &status, 0);
	free_all_alloc_items(pipex);
}
