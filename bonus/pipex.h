/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 05:13:57 by hel-omra          #+#    #+#             */
/*   Updated: 2024/04/19 23:32:33 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_vrs
{
	char	**path;
	int		p[2];
	int		fd_infile;
	int		fd_outfile;
	int		pid1;
	int		pid2;
}	t_vrs;

//utils
size_t	ft_strlen(char *s);
size_t	ft_strlen2d(char **s);
char	*trim_end(char *s);
char	is_quote(char *s);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s, char *buffer);
char	*ft_strdup(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	putstr_fd(char *s, int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);

//errors
void	free2d(char **s, int i);
void	ft_error(char *s, t_vrs *pipex);

#endif