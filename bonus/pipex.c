/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/05/02 05:37:48 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **command, char **env, t_vrs *px)
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
				ft_error("path ", px);
			}
		}
	}
	free2d(paths, ft_strlen2d(paths));
	return (path);
}

void	create_child(char *av, char **env, t_vrs *px)
{
	char	**command;
	char	*path;

	if (dup2(px->p[1], STDOUT_FILENO) < 0)
		ft_error("dup2 ", px);
	(close(px->p[1]), close(px->fd_infile), (close(px->p[0])));
	command = ft_split(av, is_quote(av));
	path = get_path(command, env, px);
	if (execve(path, command, env) < 0)
	{
		free2d(command, ft_strlen2d (command));
		ft_error("execve ", px);
	}
}

void	pipes(t_vrs *px, char **av, char **env, int ac)
{
	if (px->flag == 1)
		px->nb = 3;
	else
		px->nb = 2;
	while (px->nb < ac - 1)
	{
		if (pipe(px->p) < 0)
			ft_error("pipe ", px);
		px->pid = fork();
		if (px->pid < 0)
			ft_error("fork ", px);
		if (px->pid == 0 && px->nb != ac - 2)
			create_child(av[px->nb], env, px);
		else if (px->pid == 0 && px->nb == ac - 2)
		{
			px->p[1] = px->fd_outfile;
			create_child(av[px->nb], env, px);
		}
		else
		{
			if (dup2(px->p[0], 0) < 0)
				ft_error("dup ", px);
			(1) && (close (px->p[0]), close (px->p[1]), px->nb++);
		}
	}
}

void	here_doc(t_vrs *px, char *s)
{
	char		*line;

	(1) && (px->flag = 1, px->pid = 1);
	px->nb = (int)&px->itoa;
	(1) && (px->nb < 0) && (px->nb *= -1);
	px->itoa = (char *)malloc(7);
	while (px->pid < 7)
		(1) && (px->itoa[px->pid++] = (px->nb % 10) + 48, px->nb /= 10);
	(1) && (px->itoa[0] = '.', px->itoa[6] = '\0');
	(1) && (px->itoa = ft_strjoin("/tmp/", px->itoa), s = ft_strjoin(s, "\n"));
	px->fd_infile = open(px->itoa, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (px->fd_infile < 0)
		(free(s), ft_error("fd ", px));
	while (1)
	{
		(putstr_fd(">> ", STDOUT_FILENO), line = get_next_line(0));
		if (!line || ft_strncmp(line, s, ft_strlen(s)) == 0)
		{
			free(s);
			if (line)
				free(line);
			break ;
		}
		(putstr_fd(line, px->fd_infile), free(line));
	}
	close(px->fd_infile);
	px->fd_infile = open(px->itoa, O_CREAT | O_RDWR, 0644);
}

int	main(int ac, char **av, char **env)
{
	t_vrs	px;
	int		j;

	(1) && (j = 0, px.flag = 0);
	if (ac < 5)
		(putstr_fd("Please insert at least 5 arguments !\n", 2), exit (1));
	if (ft_strncmp(av[1], "here_doc", 8) == 0
		&& ft_strlen(av[1]) == 8 && ac == 5)
		(putstr_fd("Invalid arguments !\n", 2), exit (1));
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ft_strlen(av[1]) == 8)
	{
		here_doc(&px, av[2]);
		px.fd_outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		px.fd_infile = open(av[1], O_RDONLY);
		px.fd_outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (px.fd_infile < 0 || px.fd_outfile < 0)
		ft_error("file ", &px);
	if (dup2(px.fd_infile, 0) < 0)
		ft_error("dup ", &px);
	pipes(&px, av, env, ac);
	if (px.flag == 1)
		(unlink(px.itoa), free(px.itoa));
	while (j++ < px.nb - 2)
		wait(NULL);
	(close(px.p[0]), close(px.p[1]), exit(0));
}
