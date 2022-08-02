/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_extractor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:56:44 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 19:56:44 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	Checks the existing command for validity by trying to combine with
 	different paths and checking them for existence with the access() function.
	If access() returns 0, it means that the path exists and can be returned.
*/
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

/*
	Gets a full path for the given command, received from argv.
*/
void	get_cmd(char **env, t_pipex *pipex, int i)
{
	char	**paths;

	pipex->cmd = ft_split(pipex->args->argv[i], ' ');
	paths = get_all_paths(env);
	pipex->cmd_path = assign_path(paths, pipex->cmd);
	free_split(paths);
}