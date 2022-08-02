/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:27:14 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 14:44:31 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

static char *assign_path(char **paths, char **cmd)
{
	int		i;
	char	*path;
	char 	*path_with_slash;
	char	*slash;

	path = NULL;
	path_with_slash = NULL;
	slash = ft_strdup("/");
	i = 0;
	while (paths[i] != NULL)
	{
		path_with_slash = ft_strjoin(paths[i], slash);
		path = ft_strjoin(path_with_slash, cmd[0]);
		free(path_with_slash);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(slash);
	slash = NULL;
	return (path);
}

/*
	Finds and returns all paths of the env var. 'PATH', separated by
 	the delimiter ':';
 	Iterate through all available env vars and compare the first 5 character.
 	If the first 5 chars are 'PATH=' - this env index contains the paths.
 	Return the pointer to 6th position (char.) of the env var
 	(the arg. 'PATH=' doesnt belong to the actual paths).
 	If no env with 'PATH=' specified, set the path to CWD.
*/
static char	**get_all_paths(char **env)
{
	int		i;
	char	*paths;

	paths = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			paths = &(env[i][5]);
		i++;
	}
	if (paths == NULL)
		paths = ft_strdup("./");
	return (ft_split(paths, ':'));
}

void	get_cmd(char **env, t_pipex *pipex, int i)
{
	char	**paths;

	pipex->cmd = ft_split(pipex->args.argv[i], ' ');
	paths = get_all_paths(env);
	pipex->cmd_path = assign_path(paths, pipex->cmd);
	free_split(paths);
}

void	parse_in_out_files(t_pipex *pipex, int index_outfile)
{
	pipex->infile = pipex->args.argv[1];
	pipex->outfile =  pipex->args.argv[index_outfile];
	if (ft_strncmp(pipex->infile, "here_doc", 8 == 0))
	{
		pipex->heredoc_used = true;
		pipex->infile = "here_doc";
		pipex->fd_in = open("/tmp/.tmp", O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
		if (pipex->fd_in < 0)
			exit_with_error(pipex, TMP_FD_ERROR);
	}
	else
	{
		pipex->heredoc_used = false;
		pipex->fd_in = open(pipex->infile, O_RDONLY);
		if (pipex->fd_in < 0 || access(pipex->infile, F_OK) < 0)
			exit_with_error(pipex, INFILE_EXIST_ERROR);
		if (pipex->fd_in < 0 || access(pipex->infile, R_OK) < 0)
			exit_with_error(pipex, INFILE_READ_ERROR);
	}
	pipex->fd_out = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	if (pipex->fd_out < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
}

void	parse_exec_commands(char **env, t_pipex *pipex)
{
	if (pipex->heredoc_used == true)
		pipe_from_heredoc(env, pipex);
	else
		pipe_from_infile(env, pipex);
}