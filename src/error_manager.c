/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:53:43 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 15:15:03 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	exit_with_error(t_pipex *pipex, int exitcode)
{
	char *str;

	if (exitcode == ARGNUM_ERROR)
		str = "\nError. Number of passed arguments is incorrect";
	else if (exitcode == PIPE_ERROR)
		str = "\nError. No pipe created";
	else if (exitcode == FORK_ERROR)
		str = "\nFork Error. No child process created";
	else if (exitcode == INFILE_ERROR)
		str = "\nError. The infile doesn't exist or you have no permissions to "
			  "open it";
	else if (exitcode == OUTFILE_ERROR)
		str = "\nError. File couldn't be created or is read-only";
	else if (exitcode == EXECVE_ERROR)
		str = "\nError. Unknown command";
	if (exitcode != ARGNUM_ERROR)
		free_all_alloc_items(pipex);
	perror(str);
	exit(exitcode);
}

