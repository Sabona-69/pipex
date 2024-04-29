/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/29 22:30:02 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	create_child(char *av, char **env, t_vrs *px)
{
	char	**command;
	char	*path;

	if (dup2(px->p[1], STDOUT_FILENO) < 0)
		ft_error("dup2 ", px);
	(close(px->p[1]), close(px->fd_infile), (close(px->p[0])));
	command = ft_split(av, is_quote(av));
	path = get_path(command, env, px);
	putstr_fd(av, 2);
	if (execve(path, command, env) < 0)
	{
		free2d(command, ft_strlen2d (command));
		ft_error("execve ", px);
	}
}

void	pipes(t_vrs *px, char **av, char **env, int ac)
{
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
			if (dup2(px->p[0], STDIN_FILENO) < 0)
				ft_error("dup ", px);
			(close (px->p[0]), close (px->p[1]));
			px->nb++;
		}
	}
}

void	here_doc(t_vrs *px, char *s)
{
	char		*line;

	(1) && (px->flag = 1, px->pid = 1, line = NULL);
	px->nb = (int)&px->itoaa;
	(1) && (px->nb < 0) && (px->nb *= -1);
	px->itoaa = (char *)malloc(7);
	while (px->pid < 7)
		(1) && (px->itoaa[px->pid++] = (px->nb % 10) + 48, px->nb /= 10);
	(1) && (px->itoaa[0] = '.', px->itoaa[6] = '\0');
	px->itoaa = ft_strjoin ("/tmp/", px->itoaa);
	px->fd_infile = open(px->itoaa, O_CREAT | O_TRUNC | O_RDONLY, 0666);
	if (px->fd_infile < 0)
		ft_error("fd ", px);
	s = ft_strjoin(s, "\n");
	putstr_fd(">> ", STDOUT_FILENO);
	line = get_next_line(0);
	while (1)
	{
		if (!line)
			return ;
		if (ft_strcmp(line, s) == 0)
		{
			(free(s), free (line));
			break ;
		}
		putstr_fd(line, px->fd_infile);
		free(line);
		line = get_next_line(0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_vrs	px;
	int		j;

	(1) && (j = 0, px.flag = 0);
	// if (ac < 5)
	// 	(putstr_fd("Please insert at least 5 arguments !\n", 2), exit (1));
	// if (ft_strcmp(av[1], "here_doc") == 0 && ac == 5)
	// 	(putstr_fd("Invalid arguments !\n", 2), exit (1));
	// if (ft_strcmp(av[1], "here_doc") == 0 && ft_strlen(av[1]) == 8)
	// 	here_doc(&px, av[2]);
	// else
	px.fd_infile = open(av[1], O_RDONLY);
	px.fd_outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (px.fd_infile < 0 || px.fd_outfile < 0)
		ft_error("file ", &px);
	if (dup2(px.fd_infile, STDIN_FILENO) < 0)
		ft_error("dup ", &px);
	px.nb = 2;
	pipes(&px, av, env, ac);
	// if (px.flag == 1)
	// 	(unlink(px.itoaa), free(px.itoaa));
	while (j++ < px.nb - 2)
		wait(NULL);
	(close(px.p[0]), close(px.p[1]), exit(0));
}
