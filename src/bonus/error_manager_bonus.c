/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:53:43 by rmazurit          #+#    #+#             */
/*   Updated: 2022/08/03 19:27:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

/*
	Exits a process or the program with an appropriate error message, based on
 	the exitcode.
 	Prints the error message to stdout.
*/
void	exit_with_error(t_pipex *pipex, int exitcode)
{
	char	*str;

	if (exitcode == ARGNUM_ERROR)
		str = "Error. Number of passed arguments is incorrect";
	else if (exitcode == INFILE_EXIST_ERROR)
		str = "Error";
	else if (exitcode == INFILE_READ_ERROR)
		str = "Error. You don't have the permissions to read from the file";
	else if (exitcode == OUTFILE_ERROR)
		str = "Error. File couldn't be created";
	else if (exitcode == TMP_FD_ERROR)
		str = "Error. Could not create a tmp file";
	else if (exitcode == PIPE_ERROR)
		str = "Pipe Error";
	else if (exitcode == FORK_ERROR)
		str = "Fork Error";
	else if (exitcode == EXECVE_ERROR)
		str = "Error. Unknown command";
	if (exitcode != ARGNUM_ERROR && exitcode != EXECVE_ERROR)
		free_cmd(pipex);
	perror(str);
	exit(exitcode);
}
