/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:27:14 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	Takes here_doc file as input file (first argument) and creates the file
 	in the tmp directory in 'hidden mode'. The file is destroyed after the first
 	piping with command unlink().
	Creates the output file (or opens if exists present) in 'append mode' to
 	implement '<< >>' commands.
*/
static void	parse_heredoc(t_pipex *pipex)
{
	pipex->fd_in = open("/tmp/.tmp", O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	if (pipex->fd_in < 0)
		exit_with_error(pipex, TMP_FD_ERROR);
	pipex->fd_out = open(pipex->outfile, O_CREAT | O_RDWR | O_APPEND, RIGHTS);
	if (pipex->fd_out < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
}

/*
	Takes infile as input file and outfile as output file.
	If input file does not exist or user has no rights to read it -
 	prints appropriate error message and exits.
	If the output file does not exist yet - creates a new one.
	When creating, the old outfile is always truncated (O_TRUNC).
*/
static void	parse_in_out_files(t_pipex *pipex)
{
	pipex->fd_in = open(pipex->infile, O_RDONLY);
	if (pipex->fd_in < 0 || access(pipex->infile, F_OK) < 0)
		exit_with_error(pipex, INFILE_EXIST_ERROR);
	if (pipex->fd_in < 0 || access(pipex->infile, R_OK) < 0)
		exit_with_error(pipex, INFILE_READ_ERROR);
	pipex->fd_out = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	if (pipex->fd_out < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
}

/*
	Checks if heredoc_used flag is true.
	If yes, pipes input via the here_doc file with LIMITER.
	Otherwise, take the infile as stdin.
*/
void	parse_exec_input(char **env, t_pipex *pipex)
{
	pipex->infile = pipex->args->argv[1];
	pipex->outfile = pipex->args->argv[pipex->args->argc - 1];
	if (ft_strncmp(pipex->infile, "here_doc", 8) == 0)
	{
		pipex->heredoc_used = true;
		parse_heredoc(pipex);
		pipe_from_heredoc(env, pipex);
	}
	else
	{
		pipex->heredoc_used = false;
		parse_in_out_files(pipex);
		pipe_from_infile(env, pipex);
	}
}
