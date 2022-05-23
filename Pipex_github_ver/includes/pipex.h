/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:51:08 by lmann             #+#    #+#             */
/*   Updated: 2022/04/02 15:40:07 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include	"../libft/includes/libft.h"

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/* to perror */
# include <stdio.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "invalid amount of inputs\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_FORK "Fork: "

# define INFILE 0
# define OUTFILE 1

typedef struct s_pipex
{
	pid_t		pid1;
	pid_t		pid2;
	int			tube[2];
	int			infile;
	int			outfile;
	char		*paths;
	char		**cmd_paths;
	char		**cmd_args;
	char		*cmd;
}	t_pipex;

int			pipex(t_pipex piping, char *argv[], char *envp[]);
void		first_child(t_pipex pipex, char *argv[], char *envp[]);
void		second_child(t_pipex pipex, char *argv[], char *envp[]);
void		msg_error(char *err);
void		close_pipes(t_pipex *piping);
void		parent_free(t_pipex piping);
void		child_free(t_pipex piping);
char		*find_path(char **envp);
int			openfile(char *filename, int mode);
int			msg(char *err);

#endif
