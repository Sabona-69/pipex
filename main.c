#include <libc.h>
#include <unistd.h>

void	free2d(char **s, int i)
{
	while (i > -1)
		free(s[i--]);
	free(s);
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
			free2d(new, k);
		k++;
	}
	new[k] = NULL;
	return (new);
}


int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *trim_end(char *s)
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

char	*ft_strjoin(char *s, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// if (!s)
	// 	return (ft_strdup(buffer));
	string = malloc(ft_strlen(s) + ft_strlen(buffer) + 1);
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
	return (string);
}

int	is_quote(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == 39)
		{
			if (s[j + 1] == 39)
				return (2);
			i++;
		} 
		j++;
	}
	if (i == 1)
		return (2);
	if (i == 2)
		return (1);
	return (0);
}
int main(int ac, char **av, char **env) 
{
	char **command;
	// printf ("{%s}\n", trim_end(av[2]));
	if (is_quote(av[2]) == 0)
		command = ft_split(av[2], ' ');
	else if (is_quote(av[2]) == 1)
		command = ft_split(av[2], 39);
	else if (is_quote(av[2]) == 2)
		printf("%s error quotes", av[2]), exit(1);
	// char *a[] = {"grep", "'", NULL};
	char *path = trim_end(*command);
	path = ft_strjoin("/usr/bin/",path);
	if (execve(path, command, env) == -1)
		perror(path);
	// while (*command)
	// 	printf("{%s}\n", *command++);
		// printf("{%s}\n", path);
}