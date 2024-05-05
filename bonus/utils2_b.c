/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:46:48 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/05 23:10:48 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_b.h"

void	putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
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

char	*ft_strjoin(char *s, char *buffer, int flag)
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
	if (flag == 1)
		free(s);
	return (string);
}

void	random_string(t_vrs *px)
{
	char	new[9];
	int		nbr;
	int		i;

	i = 1;
	nbr = (int)&new;
	(1) && (nbr < 0) && (nbr *= -1);
	while (i < 9)
	{
		new[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	(1) && (new[0] = '.', new[8] = '\0');
	px->itoa = ft_strjoin("/tmp/", new, 0);
}
