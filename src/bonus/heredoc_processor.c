/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:40:44 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 19:24:17 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

static void	read_to_stdout(t_pipex *pipex)
{
	char	*input;
	char	*limiter;
	int 	lim_len;
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

static void redirect_read_to_tmp(t_pipex *pipex)
{
	pipex->fd_in = open("/tmp/.tmp", O_RDONLY);
	if (pipex->fd_in < 0)
		exit_with_error(pipex, TMP_FD_ERROR);
	dup2(pipex->fd_in, STDOUT_FILENO);
	unlink("/tmp/.tmp");
}

void	pipe_from_heredoc(char **env, t_pipex *pipex)
{
	int 	i;
	int 	index_outfile;
	int 	last_cmd;

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
