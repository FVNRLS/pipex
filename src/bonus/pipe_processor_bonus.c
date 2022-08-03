/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processor_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:18:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	Replaces stdin with infile and passes the output via to the first command
 	via the pipe.
	If the command fails - terminates the program.
	To do this, first open the pipe and create a fork with (parent + child).
	The command is always executed on the child and the parent always waits
 	until the child is ready to pass the output to next command via the pipe.
 	If the status is not 0, it means the command failed -> exit the program!
	The unused ends of the pipe are closed and the output of the command becomes
 	the new input for the next command.
*/
void	pipe_infile(char **env, t_pipex *pipex, int i)
{
	int	status;

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
	close(pipex->fd_in);
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[0]);
}

/*
	Takes the output of the previous command and transfers it to next command.
	Basic behaviour is the same as in pipe_infile().
*/
void	pipe_inter(char **env, t_pipex *pipex, int i)
{
	int	status;

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

/*
	Takes the output of the previous command and writes it to outfile.
	Basic behaviour is the same as in pipe_infile(), with only one difference:
 	here is no pipe needed anymore, because the output can just be duplicated
 	to outfile with dup2().
*/
void	pipe_outfile(char **env, t_pipex *pipex, int i)
{
	int	status;

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

/*
	The function is executed if the input comes from the infile.
 	Executes a command, related to argv index.

 	Iteration:
	Starts with argument 2 (the first command) and iterates until last command.
	If the index is on the last command, execute the command and pass the
 	output to the outfile.
*/
void	pipe_from_infile(char **env, t_pipex *pipex)
{
	int	i;
	int	index_outfile;
	int	last_cmd;

	index_outfile = pipex->args->argc - 1;
	last_cmd = index_outfile - 1;
	i = 2;
	while (i < index_outfile)
	{
		if (i == 2)
			pipe_infile(env, pipex, i);
		else if (i != last_cmd)
			pipe_inter(env, pipex, i);
		else if (i == last_cmd)
		{
			pipe_outfile(env, pipex, i);
			exit (EXIT_SUCCESS);
		}
		i++;
	}
}
