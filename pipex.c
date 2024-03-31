/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/03/31 07:06:01 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	is_quote(char *s)
{
	while (*s)
	{
		if (*s == 39)
			return (39);
		s++;
	}
	return (32);
}

char	**get_path(char **env)
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
	while (env[j][i] != '/')
		i++;
	new = ft_split(&env[j][i], ':');
	j = 0;
	while (new[j])
	{
		new[j] = ft_strjoin(new[j], "/");
		j++;
	}
	return (new);
}

void	child_1(t_vrs *pipex, char **av, char **env)
{
	char	**f_command;
	char	*command;
	int		j;

	j = 0;
	command = trim_end(av[2]);
	close(pipex->p[0]);
	pipex->fd_infile = open(av[1], O_CREAT | O_RDONLY, 444);
	if (pipex->fd_infile < 0)
		ft_error("infile ", &pipex);
	dup2(pipex->fd_infile, 0);
	f_command = ft_split(command, is_quote(command));
	dup2(pipex->fd_infile, 0);

	while (pipex->path[j])
	{
		if (access(command, F_OK | X_OK))
			command = ft_strjoin(pipex->path[j], *f_command);
		if (access(command, F_OK | X_OK) == 0)
			break ;
		j++;
		if (!pipex->path[j])
			perror(pipex->path[j]);
		execve(command, f_command, env);
		exit (0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;
	char	**path;
	int		pid1;

	if (ac != 5)
		return (1);
	pipex.path = get_path(env);
	pipe(pipex.p);
	dup2(0, pipex.p[1]);
	close(pipex.p[0]);
	pid1 = fork();
	if (pid1 == 0)
		child_1(&pipex, av, env);
	
}
