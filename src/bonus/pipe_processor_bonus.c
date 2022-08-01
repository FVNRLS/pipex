/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:18:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/01 13:12:20 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

void	pipe_in_to_out(char **env, t_pipex *pipex, int i)
{
	int   	status;

	if (pipe(pipex->pipe) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	get_cmd(env, pipex, i);
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		exit_with_error(pipex, FORK_ERROR);
	else if (pipex->pid[0] == 0)
		exec_first_cmd(env, pipex);
	waitpid(pipex->pid[0], &status, 0);
	if (status != 0)
		exit(EXIT_FAILURE);
	clear_cmd(pipex);
	get_cmd(env, pipex, (i + 1));
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
		exit_with_error(pipex, FORK_ERROR);
	else if (pipex->pid[1] == 0)
		exec_last_cmd(env, pipex);
	close_pipes(pipex);
	waitpid(pipex->pid[1], &status, 0);
	clear_cmd(pipex);
}

void	pipe_in_to_inter(char **env, t_pipex *pipex, int i)
{
	int   	status;

	if (pipe(pipex->pipe) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	get_cmd(env, pipex, i);
	pipex->pid[1] = fork();
	if (pipex->pid[1] < 0)
		exit_with_error(pipex, FORK_ERROR);
	if (pipex->pid[1] == 0)
		exec_inter_cmd(env, pipex);
	close_pipes(pipex);
	waitpid(pipex->pid[1], &status, 0);
	clear_cmd(pipex);
}