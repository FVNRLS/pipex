/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:14:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/30 16:26:04 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	check_open_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0 || access(infile, F_OK) < 0)
		exit_with_error("Error the infile doesn't exist or you have no "
						"permissions to open it. ", INFILE_ERROR);
	return (fd);
}

int	check_open_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WTC, RIGHTS);
	if (fd < 0 || access(outfile, F_OK) < 0)
		exit_with_error("Error the outfile doesn't exist or you have no "
						"permissions to open it. ", INFILE_ERROR);
	return (fd);
}
