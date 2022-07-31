/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:14:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 14:16:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	check_open_infile(char *infile)
{
	int	fd;

	return (fd);
}

/*
	O_TRUNC truncates (empties) regular writable file when opened.
	O_RDWR = O_RDWR and O_WRONLY -> open in readable and writeable mode.
	O_CREAT = creates a new file if the file doesn't exist.
 	PERMISSIONS is a macro defined in /incl/pipex.h and sets initial permissions
 	to the created file.
*/
int	check_open_outfile(char *outfile)
{
	int	fd;


	return (fd);
}
