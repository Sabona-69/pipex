/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/03 16:49:47 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	child_1(t_vrs *pipex, char *av, char **env)
{
	char	**command;
	char	*path;

	if (dup2(pipex->fd_infile, 0) < 0 || dup2(pipex->p[1], 1) < 0)
		ft_error("dup2 ", pipex);
	close_all(pipex);
	command = ft_split(av, ' ');
	if (!command)
		ft_error("malloc ", pipex);
	path = get_path(command, env, pipex);
	if (execve(path, command, env) < 0)
	{
		free2d(command, ft_strlen2d (command));
		ft_error("execve ", pipex);
	}
}

void	child_2(t_vrs *pipex, char *av, char **env)
{
	char	**command;
	char	*path;

	if (dup2(pipex->p[0], 0) < 0 || dup2(pipex->fd_outfile, 1) < 0)
		ft_error("dup2 ", pipex);
	close_all(pipex);
	command = ft_split (av, ' ');
	if (!command)
		ft_error("malloc ", pipex);
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
		child_1(&pipex, av[2], env);
	else
	{
		pipex.pid2 = fork();
		if (pipex.pid2 < 0)
			ft_error("Fork ", &pipex);
		if (pipex.pid2 == 0)
			child_2(&pipex, av[ac - 2], env);
	}
	(close_all(&pipex), wait(NULL), wait(NULL), exit(0));
}
