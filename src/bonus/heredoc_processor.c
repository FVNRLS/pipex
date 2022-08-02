/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:40:44 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 14:39:18 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

char	*read_to_tmp(t_pipex *pipex)
{
	char	*input;
	bool	limiter_found;
	char	*limiter;
	int 	lim_len;

	limiter = ft_strjoin(ft_strdup(pipex->args.argv[2]), ft_strdup("\n"));
	lim_len = ft_strlen(limiter);
	dup2(pipex->fd_in, STDOUT_FILENO);
	close(pipex->fd_in);
	limiter_found = false;
	while (limiter_found != true)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL || ft_strncmp(input, limiter, lim_len) == 0)
			limiter_found = true;
		else
			ft_printf("%s", input);
		free(input);
	}
	free(limiter);
	return ("/tmp/.tmp");
}

void	pipe_from_heredoc(char **env, t_pipex *pipex)
{
	int 	i;
	int 	index_outfile;
	int 	last_cmd;

	index_outfile = pipex->args.argc - 1;
	last_cmd = index_outfile - 1;
	read_to_tmp(pipex);
	i = 3;
	while (i < index_outfile)
	{
		if (i == 3)
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
