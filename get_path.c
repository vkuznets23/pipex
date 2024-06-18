/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:08 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/18 11:01:54 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_func(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	malloc_failure(char **ar1, char **ar2)
{
	free_func(ar1);
	free_func(ar2);
	exit(1);
}

char	*get_envp(char **envp, char **cmd)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (&envp[i][5]);
	}
	free_func(cmd);
	exit(EXIT_FAILURE);
}

int	ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **cmd, char **envp)
{
	char	**all_paths;
	char	*path_part;
	char	*path_to_cmd;
	int		i;

	i = -1;
	if (ft_strchr(cmd[0], '/') == 1)
	{
		//check if we have accsess
		if (access(cmd[0], F_OK) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(*cmd, 2);
			free_func(cmd);
			exit(EXIT_FAILURE);
		}
		if (access(cmd[0], X_OK) == -1)
		{
			//permissiom denied or smth like thst
			ft_putstr_fd("pipex: permission denied ", 2);
			free_func(cmd);
			exit(EXIT_FAILURE);
		}
		return(cmd[0]);
	}
	all_paths = ft_split(get_envp(envp, cmd), ':');
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		if (!path_part)
			malloc_failure(cmd, all_paths);
		path_to_cmd = ft_strjoin(path_part, cmd[0]);
		free(path_part);
		if (!path_to_cmd)
			malloc_failure(cmd, all_paths);
		if (access(path_to_cmd, F_OK | X_OK) == 0)
		{
			free_func(all_paths);
			return (path_to_cmd);
		}
		free(path_to_cmd);
	}
	free_func(all_paths);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(*cmd, 2);
	free(cmd);
	exit(1);
}

//line 71: we malloc at this step cmd, all_paths, path_to_cmd, BUT we use cmd and path_to_cmd AND free_path is already been free
