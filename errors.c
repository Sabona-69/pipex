/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:45:27 by hel-omra          #+#    #+#             */
/*   Updated: 2024/03/24 00:07:25 by hel-omra         ###   ########.fr       */
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
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
	putstr_fd(s, 2);
	exit(1);
}

