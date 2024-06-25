/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:06:48 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/24 13:31:42 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initilize_data(char **av, char **envp, int ac, t_pipex *data)
{
	data->av = av;
	data->envp = envp;
	data->ac = ac;
}
