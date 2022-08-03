/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:27:14 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 13:18:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/*
	Checks the existing command for validity by trying to combine it with
 	different paths and checking them for existence with the access() function.
	If access() returns 0, it means that the path exists and can be returned.
*/
static char	*assign_path(char **paths, char **cmd)
{
	int		i;
	char	*path;
	char	*path_with_slash;
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

/*
	Gets a full paths of the first and last commands, received from argv.
*/
static void	get_commands(char **argv, char **env, t_pipex *pipex)
{
	char	**paths;

	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	paths = get_all_paths(env);
	pipex->cmd1_path = assign_path(paths, pipex->cmd1);
	pipex->cmd2_path = assign_path(paths, pipex->cmd2);
	free_split(paths);
}

/*
	If number of arguments is not 4 -> exit the program.
 	Otherwise: gather the names of infile and outfile as well as the
 	command paths over argv indexes.
*/
void	parse_input(int argc, char **argv, char **env, t_pipex *pipex)
{
	if (argc != 5)
		exit_with_error(pipex, ARGNUM_ERROR);
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	get_commands(argv, env, pipex);
}
