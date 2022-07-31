/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:08:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/07/31 15:16:58 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

typedef struct s_pipex
{
	int		pipe[2];
	pid_t	pid[2];
	char	*infile;
	char	*outfile;
	char 	**cmd1;
	char 	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
}				t_pipex;

# define	ARGNUM_ERROR		1
# define 	PIPE_ERROR			2
# define	FORK_ERROR			3
# define	INFILE_ERROR		4
# define	OUTFILE_ERROR		5
# define	EXECVE_ERROR		6
# define	PERMISSIONS			0644

//CORE FUNCTIONS
void	parse_input(int argc, char **argv, char **env, t_pipex *pipex);
void	exec_cmd1(char **env, t_pipex *pipex);
void	exec_cmd2(char **env, t_pipex *pipex);

//PIPES MANAGER
void	close_pipes(t_pipex *pipex);

//UTILS
void	exit_with_error(t_pipex *pipex, int exitcode);

//TOOLS
void	free_split(char **split);
void	free_all_alloc_items(t_pipex *pipex);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);



#endif
