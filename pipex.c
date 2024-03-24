/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:16:40 by hel-omra          #+#    #+#             */
/*   Updated: 2024/03/24 00:11:20 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pipex->fd_infile = open(av[1], O_CREAT | O_RDONLY, 444);
	if (pipex->fd_infile < 0)
		ft_error("Fail to open file !\n", pipex);
	f_command = ft_split(av[2], ' ');
	dup2(pipex->fd_infile, 0);
	while (pipex->path[j])
	{
		command = ft_strjoin(pipex->path[j], *f_command);
		if (access(command, F_OK | X_OK) == 0)
			break ;
		j++;
		if (!pipex->path[j])
		{
			ft_error(av[2], pipex);
			ft_error(" : command not found !\n", pipex);
		}
		execve(command, f_command, env);
		exit (0);
	}

}

int	main(int ac, char **av, char **env)
{
	t_vrs	pipex;
	int		p[2];
	char	**path;
	int		pid1;

	if (ac != 5)
		return (0);
	pipex.path = get_path(env);
	pipe(pipex.p);
	pid1 = fork();
	if (pid1 == 0)
		child_1(&pipex, av, env);

}