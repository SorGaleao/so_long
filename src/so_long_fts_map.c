/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_fts_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:10 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/12/02 16:31:26 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	if (game->img)
	{
		if (game->img->img_w || game->img->img_p || game->img->img_e
			|| game->img->img_c || game->img->img_g)
			ft_destroy_img(game);
		free(game->img);
		game->img = NULL;
	}
	ft_clean_map(game);
	if (game->map)
	{
		free(game->map);
		game->map = NULL;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (exit(0), 0);
}

static int	ft_flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map->rows || y >= game->map->bricks)
		return (0);
	if (game->map->copy_map[x][y] == 'E')
		game->map->copy_map[x][y] = '1';
	if (game->map->copy_map[x][y] == '1' || game->map->copy_map[x][y] == 'V')
		return (0);
	game->map->copy_map[x][y] = 'V';
	ft_flood_fill(game, x + 1, y);
	ft_flood_fill(game, x - 1, y);
	ft_flood_fill(game, x, y + 1);
	ft_flood_fill(game, x, y - 1);
	return (0);
}

static int	ft_surrounded_by_walls(t_game *game)
{
	while (game->map->map_text[0]
		&& game->map->map_text[0][game->map->bricks_w] != '\n')
	{
		if (game->map->map_text[0][game->map->bricks_w++] != '1')
			return (-1);
	}
	game->map->bricks_w = 0;
	while (game->map->map_text[game->map->rows - 1][game->map->bricks_w]
		&& game->map->map_text[game->map->rows
		- 1][game->map->bricks_w] != '\n')
	{
		if (game->map->map_text[game->map->rows - 1][game->map->bricks_w] \
			!= '1')
			return (-1);
		game->map->bricks_w++;
	}
	game->map->rows_w = 1;
	while (game->map->rows_w < game->map->rows - 1)
	{
		if (game->map->map_text[game->map->rows_w][0] != '1'
			|| game->map->map_text[game->map->rows_w][game->map->bricks_w
			- 1] != '1')
			return (-1);
		game->map->rows_w++;
	}
	return (0);
}

int	map_is_valid(t_game *game)
{
	int	i;
	int	j;

	if (game->map->count_e != 1 || game->map->count_p != 1
		|| game->map->collec < 1)
		return (perror("Invalid Map: the map must contain at least 1  \
			collectable and only 1 player and exit"), -1);
	i = 0;
	ft_flood_fill(game, game->map->player_x, game->map->player_y);
	while (i < game->map->rows)
	{
		j = 0;
		while (j < game->map->bricks)
		{
			if (game->map->copy_map[i][j] == 'C'
				|| game->map->copy_map[i][j] == 'E')
				return (perror("Invalid Map: collectable \
						or exit not accessible"), -1);
			j++;
		}
		i++;
	}
	if (ft_surrounded_by_walls(game) == -1)
		return (perror("Invalid Map: not surrounded by walls"), -1);
	return (0);
}

int	draw_map(t_game *game)
{
	game->l = 0;
	game->map->line_map = get_next_line(game->map->fd_map);
	while (game->map->line_map)
	{
		game->map->map_text[game->l] = ft_strdup(game->map->line_map);
		game->map->copy_map[game->l] = ft_strdup(game->map->line_map);
		game->col = 0;
		while (game->map->line_map[game->col] != '\n'
			&& game->map->line_map[game->col])
		{
			if (put_image(game) == -1)
				return (free(game->map->line_map), -1);
			game->col++;
		}
		game->l++;
		free(game->map->line_map);
		game->map->line_map = get_next_line(game->map->fd_map);
	}
	game->map->map_text[game->l] = NULL;
	game->map->copy_map[game->l] = NULL;
	if (map_is_valid(game) == -1)
		return (-1);
	return (0);
}
