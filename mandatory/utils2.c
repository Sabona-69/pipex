/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:46:48 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/02 23:11:36 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	putstr_fd(char *s, int fd)
{
	while (*s)
		write (fd, s++, 1);
}

int	ft_strcmp(const char *s1, const char *s2, size_t n)

{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
		i++;
	if (i == n)
		return (0);
	return (1);
}

char	*ft_strjoin(char *s, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s && buffer)
		return (ft_strdup(buffer));
	if (!buffer && s)
		return (ft_strdup(s));
	string = malloc(ft_strlen(s) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	while (s[i])
	{
		string[i] = s[i];
		i++;
	}
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (string);
}

void	close_all(t_vrs *px)
{
	close(px->fd_infile);
	close(px->fd_outfile);
	close(px->p[0]);
	close(px->p[1]);
}
