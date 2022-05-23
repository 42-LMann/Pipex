/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:29:46 by lmann             #+#    #+#             */
/*   Updated: 2022/05/23 15:12:08 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* 	Main function of pipex is to open pipes, divert the sub process
	associated with each child process by fork() while the parent process
	waits for those sub processes to complete then. once the child 
	processes have completed, the parent will then close the 
	infile and outfile and then free the command pathway.
	
	This process also finds the PATH, (pathway for CMD commands) 
	and separates it path into multiple pointers using the ':' as the 
	delimiter. More in pipex_utils.c */

int	pipex(t_pipex piping, char *argv[], char *envp[])
{
	piping.paths = find_path(envp);
	piping.cmd_paths = ft_split(piping.paths, ':');
	pipe(piping.tube);
	piping.pid1 = fork();
	if (piping.pid1 < 0)
		msg_error(ERR_FORK);
	if (piping.pid1 == 0)
	{
		first_child(piping, argv, envp);
		waitpid(piping.pid1, NULL, 0);
	}
	piping.pid2 = fork();
	if (piping.pid2 < 0)
		msg_error(ERR_FORK);
	if (piping.pid2 == 0)
	{
		second_child(piping, argv, envp);
		waitpid(piping.pid2, NULL, 0);
	}
	close_pipes(&piping);
	parent_free(piping);
	return (0);
}

/*	Uses arguments from command line to check if files exist with "openfile",
	checks for correct amount of arguments before inputting into key pipex 
	function. */

int	main(int argc, char *argv[argc], char *envp[])
{
	t_pipex	piping;

	if ((argc != 5))
		return (msg(ERR_INPUT));
	piping.infile = openfile(argv[1], INFILE);
	piping.outfile = openfile(argv[4], OUTFILE);
	if (pipe(piping.tube) < 0)
		msg_error(ERR_PIPE);
	pipex(piping, argv, envp);
	return (0);
}

/* each cmd needs a stdin (input) and returns an output (to stdout)
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    tube[1]       ↔       tube[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  tube[0]
           output                             reads tube[1]
         is written                          and sends cmd1
          to tube[1]                          output to cmd2
       (tube[1] becomes                      (tube[0] becomes 
        cmd1 stdout)                           cmd2 stdin)       */