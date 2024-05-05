/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:45:27 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/05 22:58:49 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	ft_strlen2d(char **s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	free2d(char **s, int i)
{
	while (i != 0)
		free(s[i--]);
	free(s);
}

void	ft_error(char *s, t_vrs *px)
{
	close(px->p[0]);
	close(px->p[1]);
	close(px->fd_infile);
	close(px->fd_outfile);
	putstr_fd(s, 2);
	exit(1);
}
