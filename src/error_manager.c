/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:53:43 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 14:12:36 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	exit_with_error(t_pipex *pipex, int exitcode)
{
	char *str;

	if (exitcode == ARGNUM_ERROR)
		str = "Error. Number of passed arguments is incorrect.\n";
	else if (exitcode == PIPE_ERROR)
		str = "Error. No pipe created.\n";
	else if (exitcode == FORK_ERROR)
		str = "Fork Error. No child process created.\n";
	else if (exitcode == INFILE_ERROR)
		str = "Error. The infile doesn't exist or you have no permissions to "
			  "open it.\n";
	else if (exitcode == OUTFILE_ERROR)
		str = "Error. File couldn't be created or is read-only.\n";
	else if (exitcode == EXECVE_ERROR)
		str = "Error. Unknown command.\n";
	if (exitcode != ARGNUM_ERROR)
		free_all_alloc_items(pipex);

	perror(str);
	exit(exitcode);
}

