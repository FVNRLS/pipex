/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:27:14 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/01 15:26:23 by rmazurit         ###   ########.fr       */
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
		paths = "./";
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

	pipex->fd_in = open(pipex->infile, O_RDONLY);
	if (pipex->fd_in < 0 || access(pipex->infile, F_OK) < 0)
		exit_with_error(pipex, INFILE_EXIST_ERROR);
	if (pipex->fd_in < 0 || access(pipex->infile, R_OK) < 0)
		exit_with_error(pipex, INFILE_READ_ERROR);

	pipex->fd_out = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC,
						 PERMISSIONS);
	if (pipex->fd_out < 0 || access(pipex->outfile, F_OK) < 0)
		exit_with_error(pipex, OUTFILE_ERROR);
}

//TODO: problem:
// ./pipex infile "cat" "cat" "cat" outfile

void	parse_exec_commands(char **env, t_pipex *pipex)
{
	int i;
	int index_outfile;
	int last_cmd;

	index_outfile = pipex->args.argc - 1;
	last_cmd = index_outfile - 1;

	i = 2;
	if (pipe(pipex->pipe1) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	if (pipe(pipex->pipe2) < 0)
		exit_with_error(pipex, PIPE_ERROR);
	while (i < index_outfile)
	{
//		if (pipex->args.argc == 5)
//		{
//			pipe_in_to_out(env, pipex, i);
//			exit (EXIT_SUCCESS);
//		}
//		else

		{
			if (i == 2)
				pipe_in_to_inter(env, pipex, i);
			else if (i != last_cmd)
				pipe_inter(env, pipex, i);
			else if (i == last_cmd)
			{
				pipe_inter_to_out(env, pipex, i);
				exit (EXIT_SUCCESS);
			}
		}
		i++;
	}
	close(pipex->pipe1[0]);
	close(pipex->pipe1[1]);
	close(pipex->pipe2[0]);
	close(pipex->pipe2[1]);
}