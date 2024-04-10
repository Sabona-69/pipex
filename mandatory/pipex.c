/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabona <sabona@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/10 14:57:38 by sabona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			// printf("[%s]\n", path);
			if (access(path, F_OK | X_OK) == 0)
				break ;
			j++;
			free(path), path = NULL;
			if (!pipex->path[j])
				(free(path), perror(pipex->path[j]));
		}
	}
	return (path);
}

void	child_1(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;

	path = trim_end(av[2]);
	close(pipex->p[0]);
	pipex->fd_infile = open(av[1], O_CREAT | O_RDONLY, 0555);
	if (pipex->fd_infile == -1)
		(free(path), ft_error("Infile ", pipex));
	if (dup2(pipex->fd_infile, 0) == -1 || dup2(pipex->p[1], 1) == -1)
		(free(path), ft_error("dup2 ", pipex));
	(close(pipex->p[1]), close(pipex->fd_infile));
	command = ft_split(path, is_quote(av[2]));
	path = get_path(command, pipex);
	if (execve(path, command, env) == -1)
		(free(path),free2d(command, ft_strlen((char*)command)), ft_error("execve ", pipex));
}

void	child_2(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;

	path = trim_end(av[3]);
	close(pipex->p[1]);
	pipex->fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex->fd_outfile == -1)
		ft_error("Outfile ", pipex);
	if (dup2(pipex->p[0], 0) == -1 || dup2(pipex->fd_outfile, 1) == -1)
		(free(path), ft_error("dup2 ", pipex));
	(close(pipex->p[0]), close(pipex->fd_outfile));
	// fprintf(stderr, "{%s}\n", path);
	command = ft_split(path,  is_quote(av[3]));
	path = get_path(command, pipex);
	if (execve(path, command, env) == -1)
		(free(path),free2d(command, ft_strlen((char*)command)), ft_error("execve ", pipex));
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
	pid1 = fork();
	if (pid1 == -1)
		ft_error("Fork ", &pipex);
	if (pid1 == 0)
		child_1(&pipex, av, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_error("Fork ", &pipex);
	if (pid2 == 0)
		child_2(&pipex, av, env);
	wait(NULL);
	// wait(NULL);
	close(pipex.p[0]);
	close(pipex.p[1]);
	free2d(pipex.path, ft_strlen((char*)pipex.path));
	exit(0);
}
