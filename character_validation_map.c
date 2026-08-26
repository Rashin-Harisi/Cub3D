/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_validation_map.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 11:00:37 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 11:00:42 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

int	character_validation(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!(map[i][j] == '0'
				|| map[i][j] == '1'
				|| map[i][j] == 'N'
				|| map[i][j] == 'S'
				|| map[i][j] == 'E'
				|| map[i][j] == 'W'
				|| map[i][j] == ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
