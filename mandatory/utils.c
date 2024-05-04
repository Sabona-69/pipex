/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 05:44:18 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/03 16:49:47 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_count_words(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char				*new;
	unsigned int		i;
	int					j;

	i = 0;
	j = 0;
	new = malloc (len + 1);
	if (!new)
		return (NULL);
	while (i++ < start)
		j++;
	i = 0;
	while (s[start] && start < len + j)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

char	**ft_split(char *s, char c)
{
	char	**new;
	int		k;
	int		i;
	int		j;

	k = 0;
	i = 0;
	j = 0;
	new = malloc ((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (k < ft_count_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		new[k] = ft_substr(s, j, i - j);
		if (!new[k])
			return (free2d(new, k), NULL);
		k++;
	}
	new[k] = NULL;
	return (new);
}

char	*ft_strdup(char	*s)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = malloc (ft_strlen(s) + 1);
	if (!s1)
		return (NULL);
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
