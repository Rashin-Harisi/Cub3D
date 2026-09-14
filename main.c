/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 10:47:51 by rabdolho          #+#    #+#             */
/*   Updated: 2026/08/26 10:49:31 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	t_info	info;
	t_game	game;

	info = (t_info){0};
	if (argc != 2)
		return (printf("Error\n"), 1);
	if (!file_extension_check(argv[1]))
		return (printf("Error\nNot valid extension\n"), 1);
	if (!read_file(argv[1], &info))
		return (free_info(&info), 1);
	if (!validate_and_normalize(&info))
		return (free_info(&info), 1);
	game.mlx = mlx_init();
	if (game.mlx == NULL) return (1);
	game.mlx_win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	if (game.mlx_win == NULL)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return (1);
	}
	mlx_hook(game.mlx_win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	free_info(&info);
	return (0);
}
