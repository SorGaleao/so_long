/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:01:10 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/12/02 16:30:17 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_icon(t_game *game)
{
	game->img->img_w = mlx_xpm_file_to_image(game->mlx, "textures/tree.xpm",
			&game->w, &game->h);
	game->img->img_g = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&game->w, &game->h);
	game->img->img_c = mlx_xpm_file_to_image(game->mlx, "textures/berry.xpm",
			&game->w, &game->h);
	game->img->img_e = mlx_xpm_file_to_image(game->mlx, "textures/door.xpm",
			&game->w, &game->h);
	game->img->img_p = mlx_xpm_file_to_image(game->mlx, "textures/fox1.xpm",
			&game->w, &game->h);
	if (!game->img->img_w || !game->img->img_g || !game->img->img_c
		|| !game->img->img_e || !game->img->img_p)
		return (perror("Error to load image"), mlx_destroy_window(game->mlx,
				game->win), -1);
	return (0);
}

static int	get_window(t_game *game)
{
	game->line = get_next_line(game->map->fd_window);
	game->map->bricks = ft_strlen(game->line);
	while (game->line != NULL)
	{
		if (ft_strlen(game->line) != game->map->bricks)
		{
			if (ft_strlen(game->line) == (game->map->bricks - 1))
			{
				free(game->line);
				game->line = get_next_line(game->map->fd_window);
				game->map->rows++;
				if (game->line == NULL)
					break ;
			}
			return (free(game->line), perror("Invalid Map format"), -1);
		}
		game->map->rows++;
		free(game->line);
		game->line = get_next_line(game->map->fd_window);
	}
	if (game->map->rows < 2 || game->map->bricks < 2)
		return (perror("Invalid Map Format"), -1);
	game->win = mlx_new_window(game->mlx, (WIDTH * game->map->bricks) - WIDTH,
			HEIGTH * game->map->rows, "So Long");
	return (close(game->map->fd_window), free(game->line), 0);
}

static int	ft_inicialize_var(t_game *game, char *argv)
{
	game->mlx = mlx_init();
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		return (perror("Failed to allocate images struct"), 1);
	game->img->img_p = NULL;
	game->img->img_w = NULL;
	game->img->img_g = NULL;
	game->img->img_c = NULL;
	game->img->img_e = NULL;
	game->map = malloc(sizeof(*game->map));
	if (!game->map)
		return (perror("Failed to allocate map struct"), 1);
	game->map->rows = 0;
	game->map->bricks = 0;
	game->map->rows_w = 0;
	game->map->bricks_w = 0;
	game->map->map_text = NULL;
	game->map->copy_map = NULL;
	game->map->player_x = 0;
	game->map->player_y = 0;
	game->map->count_p = 0;
	game->map->count_e = 0;
	game->map->collec = 0;
	game->map->fd_map = open(argv, O_RDONLY);
	game->map->fd_window = open(argv, O_RDONLY);
	if (game->map->fd_window < 0 || game->map->fd_map < 0)
		return (perror("Failed to open file"), 1);
	game->movements = 0;
	return (0);
}

static int	is_type_ber(char *argv, char *type)
{
	int	len;
	int	i;
	int	j;

	if (!argv)
		return (perror("Error: compiling without file"), -1);
	len = ft_strlen(argv);
	if (len < 4)
		return (perror("Invalid file format"), -1);
	i = len - 4;
	j = 0;
	if (ft_isalnum(argv[i - 1]) == 0 && \
		argv[i - 1] != '-' && argv[i - 1] != '_')
		return (perror("Invalid file format"), -1);
	while (i < len)
	{
		if (argv[i] != type[j])
			return (perror("Invalid file format"), -1);
		i++;
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || is_type_ber(argv[1], ".ber") == -1)
		return (-1);
	if (ft_inicialize_var(&game, argv[1]) != 0)
		return (close_window(&game), -1);
	if (get_window(&game) == -1)
		return (close_window(&game), -1);
	game.map->map_text = malloc((game.map->rows + 1) * sizeof(char *));
	game.map->copy_map = malloc((game.map->rows + 1) * sizeof(char *));
	if (!game.map->map_text || !game.map->copy_map)
		return (close_window(&game), -1);
	if (get_icon(&game) == -1)
		return (close_window(&game), -1);
	if (draw_map(&game) == -1)
		return (close_window(&game), -1);
	close(game.map->fd_map);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
