/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:00:50 by lmann             #+#    #+#             */
/*   Updated: 2022/04/02 15:34:53 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/*	joins cmd PATH together, previously separated by delimiter ':'
	with delimiter '/' */

void	first_child(t_pipex piping, char *argv[], char *envp[])
{
	dup2(piping.tube[1], 1);
	close(piping.tube[0]);
	dup2(piping.infile, 0);
	piping.cmd_args = ft_split(argv[2], ' ');
	piping.cmd = get_cmd(piping.cmd_paths, piping.cmd_args[0]);
	if (!piping.cmd)
	{
		child_free(piping);
		msg(ERR_CMD);
		exit(1);
	}
	execve(piping.cmd, piping.cmd_args, envp);
}

/*	First child process involving Infile(0) and cmd1(tube[1]). */

void	second_child(t_pipex piping, char *argv[], char *envp[])
{
	dup2(piping.tube[0], 0);
	close(piping.tube[1]);
	dup2(piping.outfile, 1);
	piping.cmd_args = ft_split(argv[3], ' ');
	piping.cmd = get_cmd(piping.cmd_paths, piping.cmd_args[0]);
	if (!piping.cmd)
	{
		child_free(piping);
		msg(ERR_CMD);
		exit(1);
	}
	execve(piping.cmd, piping.cmd_args, envp);
}

/*	Second child process involving cmd2(tube[0]) and Outfile(1) */

/*------------------------------------*/
/*         ------------------         */
/*  0      |     Stdin      |         */
/*         ------------------         */
/*  1      |     Stdout     |         */
/*         ------------------         */
/*  2      |     Stderr     |         */
/*         ------------------         */
/*  3      |     infile     |         */
/*         ------------------         */
/*  4      |     outfile    |         */
/*         ------------------         */
/*  5      |     tube[0]    |         */
/*         ------------------         */
/*  6      |     tube[1]    |         */
/*         ------------------         */
/*------------------------------------*/