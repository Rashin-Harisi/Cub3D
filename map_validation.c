/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:36:38 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:41:14 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

void	get_max_col_and_row(t_info *info)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	info->max_col = 0;
	while (info->map[i])
	{
		len = ft_strlen(info->map[i]);
		if (len > info->max_col)
			info->max_col = len;
		i++;
	}
	info->row = i;
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	only_one_player(t_info *info)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (is_player(info->map[i][j]))
			{
				count++;
				info->player[0] = i;
				info->player[1] = j;
				info->player_dir = info->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	map_validation(t_info *info)
{
	if (!info || !info->map || !info->map[0])
		return (0);
	if (!character_validation(info->map))
		return (printf("charcter\n"), 0);
	get_max_col_and_row(info);
	if (!wall_validation(info))
		return (printf("wall\n"), 0);
	if (!only_one_player(info))
		return (printf("player\n"), 0);
	if (!playable_tile(info->map))
		return (printf("playable\n"), 0);
	return (1);
}
