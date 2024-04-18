/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabona <sabona@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/17 16:55:39 by sabona           ###   ########.fr       */
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
	close(pipex->fd_outfile);
	if (dup2(pipex->fd_infile, 0) == -1 || dup2(pipex->p[1], 1) == -1)
		(free(path), ft_error("dup2 ", pipex));
	(close(pipex->p[1]), close(pipex->fd_infile));
	command = ft_split(path, is_quote(av[2]));
	path = get_path(command, pipex);
	if (execve(path, command, env) == -1)
		(free(path),free2d(command, ft_strlen((char*)command)), ft_error("execve ", pipex));
}

void	child_2(t_vrs *pipex, char **av, char **env, int ac, int nx)
{
	char	**command;
	char	*path;
	int		fd;
	path = trim_end(av[nx]);
	if (nx != ac - 2)
		fd = pipex->fd_outfile;
	else
		fd = pipex->p[1];
	if (dup2(pipex->p[0], 0) < 0 || dup2(fd, 1) < 0)
		ft_error("dup2 ", pipex);
	(close(pipex->p[0]), close(pipex->p[1]));
	command = ft_split(path,  is_quote(av[nx]));
	path = get_path(command, pipex);
	if (execve(path, command, env) == -1)
		(free(path),free2d(command, ft_strlen((char*)command)), ft_error("execve ", pipex));
}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;
	int		cmds;
	int		pid1;
	int		pid2;
	int		next_cmd;

	next_cmd = 3;
	if (ac < 5)
		return(1);
	pipex.fd_infile = open(av[2], O_RDONLY, 0555);
	pipex.fd_outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0555);
	if (pipex.fd_infile < 0 || pipex.fd_outfile < 0)
		ft_error("file ", &pipex);
	if (pipe(pipex.p) < 0)
		ft_error("pipe ", &pipex);
	cmds = ac - 4;
	pid1 = fork();
	if (pid1 == 0)
		child_1(&pipex, av, env);
	while (cmds--)
	{
		// fprintf(stdout, "%d\n", cmds);
		// fprintf(stdout, "%d\n", next_cmd);
		pid2 = fork();
		if (pid2 == 0)
			child_2(&pipex, av, env, ac, next_cmd);
		next_cmd++;
	}

}
