/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:35:31 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:36:13 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int path_validation(char *path)
{
	int fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int texture_validation(t_texture *textures)
{
	if (!path_validation(textures->EA))
		return (0);
	if (!path_validation(textures->NO))
		return (0);
	if (!path_validation(textures->SO))
		return (0);
	if (!path_validation(textures->WE))
		return (0);
	return (1);
}
