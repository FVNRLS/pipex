/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_commands_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:46:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	<Child process>
	Takes the input from the input file (be it her_doc or the infile) and passes
	it as output to the first end of the opened pipe.

 	Closes unused pipe end before passing and used - after passing.
 	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
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

/*
	<Child process>
	Takes the output from the previous command via the last end of the pipe and
 	passes it to the next end of the pipe.

	Closes unused pipe end before passing and used - after passing.
  	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
void	exec_inter_cmd(char **env, t_pipex *pipex)
{
	close(pipex->pipe[0]);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);
	if (execve(pipex->cmd_path, pipex->cmd, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

/*
	<Child process>
	Takes the output from the last command and passes it as output to outfile.
	Executes the command with execve().

	Closes the duplicated fd after using.
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
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
