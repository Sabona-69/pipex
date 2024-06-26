/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/05 23:01:43 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**env_path(char **env, t_vrs *px)
{
	char	**new;
	int		j;
	int		i;

	(1) && (i = 0, j = 0);
	while (env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
			break ;
		j++;
		if (env[j] == NULL)
			ft_error("pipex : command not found\n", px);
	}
	while (env[j][i] && env[j][i] != '/')
		i++;
	new = ft_split(&env[j][i], ':');
	if (!new)
		(putstr_fd("Invalid enviroments !\n", 2), exit(1));
	j = -1;
	while (new[++j])
		new[j] = ft_strjoin(new[j], "/");
	return (new);
}

char	*get_path(char **command, char **env, t_vrs *pipex)
{
	char	**paths;
	char	*path;
	int		j;

	(1) && (j = 0, paths = env_path(env, pipex));
	if (access(command[0], F_OK | X_OK) == 0)
		path = ft_strdup(command[0]);
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
				ft_error("pipex : command not found\n", pipex);
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
		ft_error("pipex : dup2 failed\n", pipex);
	close_all(pipex);
	command = ft_split(av, ' ');
	if (!command)
		ft_error("pipex : malloc failed\n", pipex);
	path = get_path(command, env, pipex);
	if (execve(path, command, env) < 0)
	{
		free2d(command, ft_strlen2d (command));
		ft_error("pipex : command not found\n", pipex);
	}
}

void	child_2(t_vrs *pipex, char *av, char **env)
{
	char	**command;
	char	*path;

	if (dup2(pipex->p[0], 0) < 0 || dup2(pipex->fd_outfile, 1) < 0)
		ft_error("pipex : dup2 failed\n", pipex);
	close_all(pipex);
	command = ft_split(av, ' ');
	if (!command)
		ft_error("pipex : malloc failed\n", pipex);
	path = get_path(command, env, pipex);
	if (execve(path, command, env) < 0)
	{
		free2d (command, ft_strlen2d (command));
		ft_error("pipex : command not found\n", pipex);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;

	if (ac != 5)
		(putstr_fd("Please insert 5 arguments !\n", 2), exit (1));
	pipex.fd_infile = open(av[1], O_RDONLY);
	pipex.fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.fd_infile < 0 || pipex.fd_outfile < 0)
		ft_error("pipex : file failed\n", &pipex);
	if (pipe(pipex.p) < 0)
		ft_error("pipex : pipe failed\n", &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_error("pipex : fork failed\n", &pipex);
	if (pipex.pid1 == 0)
		child_1(&pipex, av[2], env);
	else
	{
		pipex.pid2 = fork();
		if (pipex.pid2 < 0)
			ft_error("pipex : fork failed\n", &pipex);
		if (pipex.pid2 == 0)
			child_2(&pipex, av[ac - 2], env);
	}
	(close_all(&pipex), wait(NULL), wait(NULL), exit(0));
}
