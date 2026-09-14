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

int close_win(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (game->mlx != NULL)
		mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
int key_hook(int keycode, void *params)
{
	t_game *game;
	game = (t_game *)params;
	if (keycode == KEY_ESC)
		close_win(game);
	else if (keycode == KEY_W)
		printf("Move forward!\n");
	else if (keycode == KEY_S)
		printf("Move backward!\n");
	else if (keycode == KEY_A)
		printf("Move Left!\n");
	else if (keycode == KEY_D)
		printf("Move Right!\n");
	else if (keycode == KEY_LEFT)
		printf("Look Left!\n");
	else if (keycode == KEY_RIGHT)
		printf("Look Right!\n");
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
	mlx_pixel_put(game.mlx,game.mlx_win, 100, 100, 0xFF0000);
	mlx_pixel_put(game.mlx,game.mlx_win, 101, 100, 0xFF0000);
	mlx_pixel_put(game.mlx,game.mlx_win, 102, 100, 0xFF0000);
	mlx_pixel_put(game.mlx,game.mlx_win, 103, 100, 0xFF0000);

	mlx_key_hook(game.mlx_win, key_hook, &game);
	mlx_hook(game.mlx_win, 17, 0, close_win, &game),
	mlx_loop(game.mlx);
	free_info(&info);
	return (0);
}
