/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:46:48 by hel-omra          #+#    #+#             */
/*   Updated: 2024/03/23 05:47:53 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	putstr_fd(char *s, int fd)
{
	while (*s)
		write (fd, s++, 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)

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
	if (!s)
		return (ft_strdup(buffer));
	string = malloc(ft_strlen(s) + ft_strlen(buffer) + 1);
	if (!string)
		return (free(s), s = NULL);
	while (s[i])
	{
		string[i] = s[i];
		i++;
	}
	while (buffer[j])
	{
		string[i] = buffer[j];
		i++;
		j++;
	}
	string[i] = '\0';
	free(s);
	return (string);
}

