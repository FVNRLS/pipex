/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/29 15:13:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

void	check_leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv)
{
	atexit(check_leaks);

}
