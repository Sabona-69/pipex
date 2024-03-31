/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:45:27 by hel-omra          #+#    #+#             */
/*   Updated: 2024/03/25 02:36:58 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free2d(char **s, int i)
{
	while (i > -1)
		free(s[i--]);
	free(s);
}

void	ft_error(char *s, t_vrs *pipex)
{
	close(pipex->p[0]);
	close(pipex->p[1]);
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
	perror(s);
	exit(1);
}
