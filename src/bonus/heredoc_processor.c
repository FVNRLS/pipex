/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:40:44 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

static void	read_to_stdout(t_pipex *pipex)
{
	char	*input;
	char	*limiter;
	int		lim_len;
	bool	limiter_found;

	limiter = ft_strjoin(ft_strdup(pipex->args->argv[2]), ft_strdup("\n"));
	lim_len = ft_strlen(limiter) + 1;
	limiter_found = false;
	while (limiter_found != true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		if (ft_strncmp(input, limiter, lim_len) == 0)
			limiter_found = true;
		else
			write(pipex->fd_in, input, ft_strlen(input));
		free(input);
	}
	free(limiter);
}

/*
	After the input from read_to_stdout() is read to the created here_doc file,
 	the content of the file should become the new output to be redirected to the
 	first command.
 	To do this:
 	1) close the file.
 	2) set the file duplicate to the new stdout with dup2().
 	3) delete the original file with unlink(), because the other processes will
 	happen on it's duplicate.
*/
static void	redirect_read_to_tmp(t_pipex *pipex)
{
	pipex->fd_in = open("/tmp/.tmp", O_RDONLY);
	if (pipex->fd_in < 0)
		exit_with_error(pipex, TMP_FD_ERROR);
	dup2(pipex->fd_in, STDOUT_FILENO);
	unlink("/tmp/.tmp");
}

/*
	The function is executed if the input is transferred via here_doc file.
 	Executes a command, related to argv index.
 	The argv[1] and argv[2] are here_doc file and its limiter and are the input,
 	that is read via terminal from user.
 	After the read input is redirected to the first command.

 	Iteration:
	Starts with argument 3 (the first command) and iterates until last command.
	If the index is on the last command, execute the command and pass the
 	output to the outfile.
*/
void	pipe_from_heredoc(char **env, t_pipex *pipex)
{
	int	i;
	int	index_outfile;
	int	last_cmd;

	index_outfile = pipex->args->argc - 1;
	last_cmd = index_outfile - 1;
	read_to_stdout(pipex);
	redirect_read_to_tmp(pipex);
	i = 3;
	while (i < index_outfile)
	{
		if (i == 3)
			pipe_infile(env, pipex, i);
		if (i != last_cmd)
			pipe_inter(env, pipex, i);
		else if (i == last_cmd)
		{
			pipe_outfile(env, pipex, i);
			exit (EXIT_SUCCESS);
		}
		i++;
	}
}
