/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:10 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/12/02 15:54:34 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static void	ft_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		WIDTH * x, HEIGTH * y);
}

int	put_image(t_game *game)
{
	ft_image(game, game->img->img_g, game->col, game->l);
	if (game->map->line_map[game->col] == '1')
		ft_image(game, game->img->img_w, game->col, game->l);
	else if (game->map->line_map[game->col] == 'E')
		return (ft_image(game, game->img->img_e, game->col, game->l), \
		game->map->count_e++, 0);
	else if (game->map->line_map[game->col] == 'C')
		return (ft_image(game, game->img->img_c, \
				game->col, game->l), game->map->collec++, 0);
	else if (game->map->line_map[game->col] == 'P')
	{
		ft_image(game, game->img->img_p, game->col, game->l);
		game->x = game->col;
		game->y = game->l;
		game->map->player_y = game->col;
		game->map->player_x = game->l;
		game->map->count_p++;
	}
	else if (game->map->line_map[game->col] == '0')
		return (0);
	else
		return (perror("Invalid character"), -1);
	return (0);
}

static int	ft_move(t_game *game, int new_y, int new_x)
{
	if (game->map->map_text[new_y][new_x] == 'E' && game->map->collec == 0)
	{
		ft_printf("Congrats, Parca, you're awesome ;)");
		close_window(game);
		return (0);
	}
	else if (game->map->map_text[new_y][new_x] != '1' \
		&& game->map->map_text[new_y][new_x] != 'E')
	{
		if (game->map->map_text[new_y][new_x] == 'C')
		{
			game->map->map_text[new_y][new_x] = '0';
			game->map->collec--;
		}
		if (game->map->map_text[game->y][game->x] == '0' || \
			game->map->map_text[game->y][game->x] == 'P')
			ft_image(game, game->img->img_g, game->x, game->y);
		ft_image(game, game->img->img_p, new_x, new_y);
		game->x = game->new_x;
		game->y = game->new_y;
		ft_printf("Movements:%i\n", game->movements);
		game->movements++;
	}
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	game->new_x = game->x;
	game->new_y = game->y;
	if (keycode == 65307)
	{
		close_window(game);
		return (0);
	}
	else if (keycode == 'w' || keycode == 65362)
		game->new_y -= 1;
	else if (keycode == 's' || keycode == 65364)
		game->new_y += 1;
	else if (keycode == 'a' || keycode == 65361)
		game->new_x -= 1;
	else if (keycode == 'd' || keycode == 65363)
		game->new_x += 1;
	ft_move(game, game->new_y, game->new_x);
	return (0);
}
