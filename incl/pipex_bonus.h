/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:43:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 18:29:36 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

typedef	struct s_args
{
	int 	argc;
	char 	**argv;
}			t_args;

typedef struct s_pipex
{
	int		pipe[2];
	pid_t	pid[2];
	char	*infile;
	char	*outfile;
	int 	fd_in;
	int 	fd_out;
	char 	**cmd_in;
	char 	**cmd_out;
	char	*cmd_in_path;
	char	*cmd_out_path;
	t_args	args;
}			t_pipex;

# define	ARGNUM_ERROR		1
# define 	PIPE_ERROR			2
# define	FORK_ERROR			3
# define	INFILE_READ_ERROR	4
# define	INFILE_EXIST_ERROR	5
# define	OUTFILE_ERROR		6
# define	EXECVE_ERROR		7
# define	PERMISSIONS			0644

//CORE FUNCTIONS
void	parse_in_out_files(t_pipex *pipex);


//ERROR MANAGER
void	exit_with_error(t_pipex *pipex, int exitcode);

//TOOLS
void	free_split(char **split);
void	free_all_alloc_items(t_pipex *pipex);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
