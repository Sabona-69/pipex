/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:45:27 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/04 17:58:14 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_b.h"

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
	if (px->flag == 1)
		free(px->itoa);
	close(px->p[0]);
	close(px->p[1]);
	close(px->fd_infile);
	close(px->fd_outfile);
	perror(s);
	exit(1);
}

char	**env_path(char **env)
{
	char	**new;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
			break ;
		j++;
	}
	while (env[j][i] && env[j][i] != '/')
		i++;
	new = ft_split(&env[j][i], ':');
	if (!new)
		(putstr_fd("Invalid env !\n", 2), exit(1));
	j = 0;
	while (new[j])
	{
		new[j] = ft_strjoin(new[j], "/", 0);
		j++;
	}
	return (new);
}

void	wait_cmds(t_vrs *px, int j)
{
	if (px->flag == 1)
		(unlink(px->itoa), free(px->itoa));
	while (j++ < px->nb - 2)
		wait(NULL);
	(close(px->fd_outfile), close(px->fd_infile));
	(close(px->p[0]), close(px->p[1]), exit(0));
}
