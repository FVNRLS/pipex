/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:13 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/29 11:20:37 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/pipex.h"

int main ()
{
	FILE *fp;

	/* first rename if there is any file */
	rename("file.txt", "newfile.txt");

	/* now let's try to open same file */
	fp = fopen("file.txt", "r");
	if( fp == NULL ) {
		perror("Error: ");
		return(-1);
	}
	fclose(fp);

	return(0);
}