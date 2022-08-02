/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_commands_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:46:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 11:10:39 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	Exec the forked child_process.
*/
void	exec_first_cmd(char **env, t_pipex *pipex)
{
	int		fd;

	close(pipex->pipe[0]);
	fd = pipex->fd_in;
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);

	if (execve(pipex->cmd_path, pipex->cmd, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

void	exec_inter_cmd(char **env, t_pipex *pipex)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);

	close(pipex->pipe[0]);
	close(pipex->pipe[1]);

	if (execve(pipex->cmd_path, pipex->cmd, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

/*
	Exec the forked parent process.
*/
void	exec_last_cmd(char **env, t_pipex *pipex)
{
	int		fd;

	fd = pipex->fd_out;

	dup2(fd, STDOUT_FILENO);

	close(fd);
	if (execve(pipex->cmd_path, pipex->cmd, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}
