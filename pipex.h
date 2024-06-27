/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:35 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/27 13:59:23 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

//struct
typedef struct s_pipex
{
	int	ac;
	char	**av;
	char	**envp;
}	t_pipex;
void	initilize_data(char **av, char **envp, int ac, t_pipex *data);
void	my_dup2(int fd_from, int fd_to, int p_fd_from, int p_fd_to);
void	exec(char *cmd, char **envp);

//last_child
void	last_child(int *p_fd, t_pipex *data);
void	last_child_fork(t_pipex *data, int *p_fd);

//error_handler.c
void	error_options(int error);
void	error_handler(char *cmd, int error, int error_status);
void	error_handler_func(char **cmd, int error, int error_status);
void	malloc_failure(char **ar1, char **ar2);
void	free_func(char **tab);

char	**ft_split(char const *s, char c);
char	*get_path(char **cmd, char **envp);

//utils2.c
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strchr(char *str, int c);
int		ft_strlen(char *str);

#endif
