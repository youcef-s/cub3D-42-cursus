/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:18:06 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/09/15 18:40:06 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*update_red(char *str)
{
	char *res;
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 'F' || str[i] == 'C')
		i++;
	res = ft_strdup(str + i);
	free (str);
	return (res);
}

int	check_chars_used(char **str)
{
	int	nbr_of_players;
	int	i;
	int	j;

	i = -1;
	nbr_of_players = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E'
			|| str[i][j] == 'E' || str[i][j] == 'W')
				nbr_of_players++;
			if (str[i][j] != '0' && str[i][j] != '1'
			&& str[i][j] != 'N' && str[i][j] != 'S'
			&& str[i][j] != 'E' && str[i][j] != 'W'
			&& str[i][j] != ' ' && str[i][j] != '\t')
				return (printf("Error\nForbidden character in the map\n"), 1);
		}
	}
	if (nbr_of_players != 1)
		return (printf("Error\nYou need ONE palyer in the map\n"), 1);
	return (0);
}

int	check_map_content(t_file *file)
{
	if (fill_scene(file))
		return (perror("Error\nmalloc"), 1);
	if (check_chars_used(file->scene))
		return (1);
	if (check_first_and_last_line(file) || check_left_wall(file)
		|| check_right_wall(file) || check_middle_lines(file))
		return (printf("Error\nThe map is not closed by walls\n"), 1);
	return (0);
}

int	check_file_content(t_file *file)
{
	char	**str;
	int		i;

	while (file->map)
	{
		str = ft_split2((char *)file->map->content, " \t");
		i = check_elements(file, str);
		if (i == 2)
			continue ;
		else if (i == 3)
			break ;
		else if (i == 1)
			return (1);
		free_2d_array(str);
		ft_lstdelone(file->map, free);
		file->map = file->map->next;
	}
	if (file->ceilling == -1 || file->floor == -1 || file->ea == 0
		|| file->we == 0 || file->no == 0 || file->so == 0)
		return (printf("Error\nMissing parameters\n"), 1);
	if (check_map_content(file))
		return (1);
	return (0);
}

int	parsing(t_file *file, int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (printf("Error\nYou need 2 arguments\n"), 1);
	if (ft_strncmp(".cub", av[1] + ft_strlen(av[1]) - 4, 4))
		return (printf("Error\nWrong file extension\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nopen"), 1);
	if (fill_lst(file, fd) && close(fd) == -1)
		return (perror("Error\nclose"), 1);
	init_vars(file);
	if (check_file_content(file))
		return (1);
	return (0);
}
