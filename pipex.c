/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:02 by hel-omra         ###   ########.fr       */
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
		if (*s == '"' || *s == '\'')
			return (*s);
		s++;
	}
	return (' ');
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

char	*get_path(char **command, t_vrs *pipex)
{
	char	*path;
	int		j;

	j = 0;
	if (access(command[j], F_OK | X_OK) == 0)
		path = ft_strdup(command[j]);
	else
	{
		while (pipex->path[j])
		{
			path = ft_strjoin(pipex->path[j], command[0]);
			if (access(path, F_OK | X_OK) == 0)
				break ;
			j++;
			// free(path);
			if (!pipex->path[j])
				perror(pipex->path[j]), exit(1);
		}
	}
	return (path);
}

void	child_1(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;
	int		j;

	j = 0;
	path = trim_end(av[2]);
	close(pipex->p[0]);
	pipex->fd_infile = open(av[1], O_CREAT | O_RDONLY, 0555);
	if (pipex->fd_infile == -1)
		ft_error("Infile ", pipex);
	if (dup2(pipex->fd_infile, 0) == -1 || dup2(pipex->p[1], 1) == -1);
		(free(path), ft_error("dup2 ", pipex));
		// close()
	command = ft_split(path, is_quote(av[2]));
	path = get_path(command, pipex);
	if (execve(path, command, env) == -1)
		(free(path),free2d(command, ft_strlen(command)), ft_error("execve ", pipex));
}

void	child_2(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;
	int		j;

	j = 0;
	path = trim_end(av[3]);
	close(pipex->p[1]);
	pipex->fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex->fd_outfile == -1)
		ft_error("Outfile ", pipex);
	dup2(pipex->p[0], 0);
	dup2(pipex->fd_outfile, 1);
	command = ft_split(path, ' ');
	path = get_path(command, pipex);
	execve(path, command, env);
}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;
	int		pid1;
	int		pid2;

	if (ac != 5)
		return (1);
	pipex.path = env_path(env);
	if (pipe(pipex.p) == -1)
		ft_error("Pipe ", &pipex);
	if ((pid1 = fork()) == -1)
		ft_error("Fork ", &pipex);
	if (pid1 == 0)
		child_1(&pipex, av, env);
	if ((pid2 = fork()) == -1)
		ft_error("Fork ", &pipex);
	if (pid2 == 0)
		child_2(&pipex, av, env);
	wait(NULL);
	wait(NULL);
	free2d(pipex.path, ft_strlen(pipex.path));
}
