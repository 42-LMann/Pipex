/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:57:14 by lmann             #+#    #+#             */
/*   Updated: 2022/04/02 15:34:56 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_free(t_pipex piping)
{
	int	i;

	i = 0;
	close(piping.infile);
	close(piping.outfile);
	while (piping.cmd_paths[i])
	{
		free(piping.cmd_paths[i]);
		i++;
	}
	free(piping.cmd_paths);
}

/*	closes infile and outfile and frees CMD command pathway 
	to CMD commands once parent process is complete*/

void	child_free(t_pipex piping)
{
	int	i;

	i = 0;
	while (piping.cmd_args[i])
	{
		free(piping.cmd_args[i]);
		i++;
	}
	free(piping.cmd_args);
	free(piping.cmd);
}

/*	frees CMD commands for the associated command arguments 
	cmd_args e.g cmd_args[0] "ls", cmd_args[1] "-la" 
	cmd e.g PATH/ls */ 