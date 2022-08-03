/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:18:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 12:04:01 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/*
	Closes all pipe ends.
*/
static void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

/*
	<Child process>
	Takes the input from the input file and passes it as output to the first end
 	of the opened pipe.

 	Closes unused pipe end before passing and used - after passing.
	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
static void	exec_cmd1(char **env, t_pipex *pipex)
{
	int		fd;

	fd = open(pipex->infile, O_RDONLY);
	if (fd < 0 || access(pipex->infile, F_OK) < 0)
		exit_with_error(pipex, INFILE_EXIST_ERROR);
	if (fd < 0 || access(pipex->infile, R_OK) < 0)
		exit_with_error(pipex, INFILE_READ_ERROR);
	dup2(fd, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	close(fd);
	if (execve(pipex->cmd1_path, pipex->cmd1, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

/*
	<Child process>
	Takes the output from the last end of the pipe and passes it to outfile.

 	Closes unused pipe end before passing and used - after passing.
	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
static void	exec_cmd2(char **env, t_pipex *pipex)
{
	int		fd;

	fd = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, PERMISSIONS);
	if (fd < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
	dup2(fd, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	close(fd);
	if (execve(pipex->cmd2_path, pipex->cmd2, env) < 0)
		exit_with_error(pipex, EXECVE_ERROR);
}

/*
	Passes the content from infile, used as input to the outfile via pipe.

 	To do this, opens the pipe and creates 2 forks with (parent and 2 children).
	The command is always executed on the first child and the parent waits
 	until the child is ready to pass the output to next command via the pipe.
 	If the status is not 0, it means the command failed -> exit the program!
 	After the first fork returns with status 0 (command executed successfully),
 	start a new fork and executes the second command with the same algorithm.
*/
void	pipe_input(char **env, t_pipex *pipex)
{
	int	status;

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
