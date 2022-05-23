/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmann <lmann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:52:21 by lmann             #+#    #+#             */
/*   Updated: 2022/04/02 15:34:55 by lmann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *piping)
{
	close(piping->tube[0]);
	close(piping->tube[1]);
}

int	msg(char *err)
{
	ft_printf("%s", err);
	return (1);
}

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
			msg_error(ERR_INFILE);
		return (open(filename, O_RDONLY, 0644));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}
