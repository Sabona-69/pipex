/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:45:27 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/05 21:18:49 by hel-omra         ###   ########.fr       */
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
	putstr_fd(s, 2);
	exit(1);
}

char	**env_path(char **env, t_vrs *px)
{
	char	**new;
	int		j;
	int		i;

	(1) && (i = 0, j = 0);
	while (env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
			break ;
		j++;		if (env[j] == NULL)
			ft_error("pipex : command not found\n", px);
	}
	while (env[j][i] && env[j][i] != '/')
		i++;
	new = ft_split(&env[j][i], ':');
	if (!new)
		(putstr_fd("Invalid enviroments !\n", 2), exit(1));
	j = -1;
	while (new[++j])
		new[j] = ft_strjoin(new[j], "/", 1);
	return (new);
}

void	wait_cmds(t_vrs *px, int j)
{
	if (px->flag == 1)
		(unlink(px->itoa), free(px->itoa));
	(close(px->fd_outfile), close(px->fd_infile));
	(close(px->p[0]), close(px->p[1])); 
	while (j++ < px->nb - 2)
		wait(NULL);
	exit(0);
}
