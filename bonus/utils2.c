/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:46:48 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/01 02:26:12 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
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
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*trim_end(char *s)
{
	char	*new;
	int		i;

	i = ft_strlen(s) - 1;
	if (s[i] != ' ')
		return (s);
	while (s[i] == ' ')
		i--;
	new = ft_substr(s, 0, i + 1);
	return (new);
}

char	is_quote(char *s)
{
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			return (*s);
		s++;
	}
	return (' ');
}
