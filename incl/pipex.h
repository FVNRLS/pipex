/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/29 11:12:43 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "structs.h"

typedef struct s_pipe
{
	int		pipe[2];
	int		pid[2];
	char	*infile;
	char	*outfile;
}				t_pipe;

#endif
