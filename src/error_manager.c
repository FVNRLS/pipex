/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:53:43 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 16:02:16 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	exit_with_error(t_pipex *pipex, int exitcode)
{
	char *str;

	if (exitcode == ARGNUM_ERROR)
		str = "Error. Number of passed arguments is incorrect";
	else if (exitcode == PIPE_ERROR)
		str = "Error. No pipe created";
	else if (exitcode == FORK_ERROR)
		str = "Fork Error. No child process created";
	else if (exitcode == INFILE_ERROR)
		str = "Error. The file does not exist or you don't have the permissions"
			  " to read from it";
	else if (exitcode == OUTFILE_ERROR)
		str = "Error. File couldn't be created";
	else if (exitcode == EXECVE_ERROR)
		str = "Error. Unknown command";
	if (exitcode != ARGNUM_ERROR && exitcode != EXECVE_ERROR)
		free_all_alloc_items(pipex);
	perror(str);
	exit(exitcode);
}

