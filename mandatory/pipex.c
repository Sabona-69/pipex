/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/26 15:32:35 by hel-omra         ###   ########.fr       */
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
		if (ft_strcmp(env[j], "PATH=", 5) == 0)
			break ;
		j++;
	}
	while (env[j][i] && env[j][i] != '/')
		i++;
	new = ft_split(&env[j][i], ':');
	if (!new)
		(putstr_fd("Invalid env !\n", 2), exit(1));
	j = 0;
	while (new[j])
	{
		new[j] = ft_strjoin(new[j], "/");
		j++;
	}
	return (new);
}

char	*get_path(char **command, char **env, t_vrs *pipex)
{
	char	**paths;
	char	*path;
	int		j;

	(1) && (j = 0, paths = env_path(env));
	if (access(command[j], F_OK | X_OK) == 0)
		path = ft_strdup(command[j]);
	else
	{
		while (paths[j])
		{
			path = ft_strjoin(paths[j], command[0]);
			if (access(path, F_OK | X_OK) == 0)
				break ;
			j++;
			free (path);
			if (!paths[j] && access(path, F_OK | X_OK) < 0)
			{
				free2d(paths, ft_strlen2d(paths));
				ft_error("path ", pipex);
			}
		}
	}
	free2d(paths, ft_strlen2d(paths));
	return (path);
}

void	child_1(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;

	close(pipex->fd_outfile);
	close(pipex->p[0]);
	if (dup2(pipex->fd_infile, 0) < 0 || dup2(pipex->p[1], 1) < 0)
		ft_error("dup2 ", pipex);
	path = trim_end(av[2]);
	(close(pipex->p[1]), close(pipex->fd_infile));
	command = ft_split(path, is_quote(av[2]));
	path = get_path(command, env, pipex);
	if (execve(path, command, env) < 0)
	{
		free2d(command, ft_strlen2d (command));
		ft_error("execve ", pipex);
	}
}

void	child_2(t_vrs *pipex, char **av, char **env)
{
	char	**command;
	char	*path;

	path = trim_end(av[3]);
	close(pipex->fd_infile);
	close(pipex->p[1]);
	if (dup2(pipex->p[0], 0) < 0 || dup2(pipex->fd_outfile, 1) < 0)
		(free(path), ft_error("dup2 ", pipex));
	(close(pipex->p[0]), close(pipex->fd_outfile));
	command = ft_split (path, is_quote(av[3]));
	path = get_path(command, env, pipex);
	if (execve(path, command, env) < 0)
	{
		free2d (command, ft_strlen2d (command));
		ft_error("execve ", pipex);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;

	if (ac != 5)
		(putstr_fd("Please insert 5 arguments !\n", 2), exit (1));
	pipex.fd_infile = open(av[1], O_RDONLY);
	pipex.fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pipex.fd_infile < 0 || pipex.fd_outfile < 0)
		ft_error("File ", &pipex);
	if (pipe(pipex.p) < 0)
		ft_error("Pipe ", &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_error("Fork ", &pipex);
	if (pipex.pid1 == 0)
		child_1(&pipex, av, env);
	else
	{
		pipex.pid2 = fork();
		if (pipex.pid2 < 0)
			ft_error("Fork ", &pipex);
		if (pipex.pid2 == 0)
			child_2(&pipex, av, env);
	}
	(close(pipex.p[0]), close(pipex.p[1]), wait(NULL), wait(NULL), exit(0));
}
