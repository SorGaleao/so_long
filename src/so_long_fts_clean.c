/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_fts_clean.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:09:07 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/12/02 15:54:36 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_clean_map_cpy(t_game *game)
{
	int	i;

	i = 0;
	if (!game->map->copy_map)
		return ;
	while (i < game->map->rows)
	{
		free(game->map->copy_map[i]);
		game->map->copy_map[i] = NULL;
		i++;
	}
	free(game->map->copy_map);
	game->map->copy_map = NULL;
}

void	ft_clean_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map->rows <= 0)
		return ;
	if (!game->map->map_text)
		return ;
	while (i < game->map->rows)
	{
		free(game->map->map_text[i]);
		game->map->map_text[i] = NULL;
		i++;
	}
	free(game->map->map_text);
	game->map->map_text = NULL;
	ft_clean_map_cpy(game);
	return ;
}

void	ft_destroy_img(t_game *game)
{
	if (!game->img)
		return ;
	if (game->img->img_p)
		mlx_destroy_image(game->mlx, game->img->img_p);
	if (game->img->img_w)
		mlx_destroy_image(game->mlx, game->img->img_w);
	if (game->img->img_g)
		mlx_destroy_image(game->mlx, game->img->img_g);
	if (game->img->img_c)
		mlx_destroy_image(game->mlx, game->img->img_c);
	if (game->img->img_e)
		mlx_destroy_image(game->mlx, game->img->img_e);
}
