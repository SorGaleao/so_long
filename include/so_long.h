/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrsouz <gabrsouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:16:16 by gabrsouz          #+#    #+#             */
/*   Updated: 2025/12/02 16:28:57 by gabrsouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef WIDTH
#  define WIDTH 32
# endif
# ifndef HEIGTH
#  define HEIGTH 32
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include "mlx.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img_p;
	void	*img_w;
	void	*img_g;
	void	*img_c;
	void	*img_e;
}			t_img;

typedef struct s_map
{
	int		rows;
	int		bricks;
	int		rows_w;
	int		bricks_w;
	char	**map_text;
	char	**copy_map;
	int		player_x;
	int		player_y;
	int		fd_map;
	int		fd_window;
	char	*line_map;
	int		count_p;
	int		count_e;
	int		collec;
}			t_map;

typedef struct s_game
{
	t_img	*img;
	t_map	*map;
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		movements;
	char	*line;
	int		l;
	int		col;
}			t_game;

char		*ft_substr(char *src, int start, int len);
char		*ft_strchr(char *str, int chr);
int			ft_strlen(char *c);
char		*ft_strdup(char *src);
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
int			ft_printf(const char *type, ...);
int			ft_is_int(int n);
int			ft_is_char(char c);
int			ft_is_str(char *str);
int			ft_is_unsigned_int(int n);
int			ft_is_percent(void);
int			ft_is_hex(unsigned long dec, const char type);
int			close_window(t_game *game);
int			draw_map(t_game *game);
int			handle_keypress(int keycode, t_game *game);
int			put_image(t_game *game);
void		ft_clean_map(t_game *game);
void		ft_destroy_img(t_game *game);
int			ft_isalnum(int c);

#endif