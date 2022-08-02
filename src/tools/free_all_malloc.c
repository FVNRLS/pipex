/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:49:12 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/02 15:32:39 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_all_alloc_items(t_pipex *pipex)
{
	if (pipex->cmd1 != NULL)
		free_split(pipex->cmd1);
	if (pipex->cmd2 != NULL)
		free_split(pipex->cmd2);
	if (pipex->cmd1_path != NULL)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path != NULL)
		free(pipex->cmd2_path);
}
