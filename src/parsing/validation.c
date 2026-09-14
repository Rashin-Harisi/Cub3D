/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:30:46 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:32:09 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int info_validation(t_info *info)
{
	if (!texture_validation(&info->textures))
		return (printf("Textures validation failed\n"), 0);
	if (!rgb_validation(info))
		return (printf("RGB validation failed\n"), 0);
	if (!map_validation(info))
		return (printf("Map validation failed\n"), 0);
	return (1);
}
