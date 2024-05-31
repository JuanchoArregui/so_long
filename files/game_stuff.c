/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:53:40 by jarregui          #+#    #+#             */
/*   Updated: 2024/05/31 17:12:13 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_strlen_no_n(char *s)
{
	int	length;

	length = ft_strlen(s);
	if (length && s[length - 1] == '\n')
		length -= 1;
	return (length);
}

void	ft_exit_error(const char *text, t_game *game)
{
	if (text != NULL && *text != '\0' && game->debug)
		ft_printf("\n❌ %s\n\n", text);
	else
		write(2, "Error\n", 6);
	ft_free_game(game);
	exit(0);
}

void	ft_free_game(t_game *game)
{
ft_printf("\n\n\n---> LIBERANDO JUEGO. check inicial map_y: %d\n", game->map_y);
	if (game->map_raw != NULL)
	{

		ft_printf("\n** Antes de liberar MAP_RAW. check inicial map_y: %d\n", game->map_y);
		free_map(game->map_raw, game->map_y);
	}
	
	if (game->map_wall != NULL)
	{
		ft_printf("\n** Antes de liberar MAP_WALL. check inicial map_y: %d\n", game->map_y);
		free_map(game->map_wall, game->map_y);
	}

	if (game->map_coll != NULL)
	{

		free_map(game->map_coll, game->map_y);
ft_printf("\nLIBERADO MAPA map_coll");
	}

	if (game->map_vstd != NULL)
	{

		free_map(game->map_vstd, game->map_y);
ft_printf("\nLIBERADO MAPA map_vstd");
	}

	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
ft_printf("\nLIBERADO WIN");
	}

	if (game->mlx)
	{

		mlx_destroy_display(game->mlx);
ft_printf("\nLIBERADO MLX");
	}

}

void	ft_get_leaks(void)
{
	ft_printf("\n\nCHECKING FOR LEAKS AT EXIT:\n");
	system("leaks -q so_long");
	ft_printf("\n");
}

void	reset_collectibles(t_game *game)
{
	game->coll_remain = 0;
	game->y = 0;
	while (game->y < game->map_y)
	{
		game->x = 0;
		while (game->x < game->map_x)
		{
			if (game->map_raw[game->y][game->x] == 'C')
			{
				game->map_coll[game->y][game->x] = 1;
				game->coll_remain += 1;
			}
			game->x++;
		}
		game->y++;
	}
	ft_printf("\n\nreset collectibles game->coll_remain: %d", game->coll_remain);
}
