#include <unistd.h>
#include <libc.h>

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
int main(int ac, char **av, char **env) 
{
	// char **f_command = ft_split(av[2], is_quote(av[2]));
	// // char *a[] = {"grep       ", "2", NULL};
	// if (execve("/usr/bin/grep", f_command, env) < 0)
	// 	perror("error :");
	printf ("{%s}", trim_end(av[1]));
}