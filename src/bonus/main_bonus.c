/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 18:50:44 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex_bonus.h"

void	check_leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.args.argc = argc;
	pipex.args.argv = argv;

//	atexit(check_leaks);

	if (argc < 5)
		exit_with_error(&pipex, ARGNUM_ERROR);
	void	parse_in_out_files(t_pipex *pipex);


	return (0);
}
