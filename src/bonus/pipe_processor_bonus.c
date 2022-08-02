/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processor_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:18:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 12:52:37 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

void	pipe_infile(char **env, t_pipex *pipex, int i)
{
	int   	status;

	if (pipe(pipex->pipe) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	get_cmd(env, pipex, i);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit_with_error(pipex, FORK_ERROR);
	else if (pipex->pid == 0)
		exec_first_cmd(env, pipex);
	waitpid(pipex->pid, &status, 0);
	if (status != 0)
		exit(EXIT_FAILURE);
	free_cmd(pipex);
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
}

void	pipe_inter(char **env, t_pipex *pipex, int i)
{
	int   	status;

	if (pipe(pipex->pipe) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	get_cmd(env, pipex, i);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit_with_error(pipex, FORK_ERROR);
	if (pipex->pid == 0)
		exec_inter_cmd(env, pipex);
	waitpid(pipex->pid, &status, 0);
	if (status != 0)
		exit(EXIT_FAILURE);
	free_cmd(pipex);
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
}


void	pipe_outfile(char **env, t_pipex *pipex, int i)
{
	int   	status;

	get_cmd(env, pipex, i);
	pipex->pid = fork();
	if (pipex->pid < 0)
		exit_with_error(pipex, FORK_ERROR);
	if (pipex->pid == 0)
		exec_last_cmd(env, pipex);
	waitpid(pipex->pid, &status, 0);
	if (status != 0)
		exit(EXIT_FAILURE);
	free_cmd(pipex);
}