/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:13:07 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/09/15 18:42:01 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_textures(char **str, t_file *file)
{
	int	i;

	i = 4;
	if (str[1][ft_strlen(str[1]) - 1] == '\n')
		i = 5;
	if (ft_strncmp(".xpm", str[1] + ft_strlen(str[1]) - i, 4))
		return (printf("Error\nWrong extension\n"), 1);
	if (str[2] && ft_strncmp(str[2], "\n", 1))
		return (printf("Error\nToo many textures\n"), 1);
	if (fill_textures(file, str))
		return (1);
	return (0);
}

int	continue_checking_colors(char **s)
{
	int		len;
	int		i;
	char	*trim;

	len = -1;
	while (++len < 3)
	{
		i = -1;
		if (len == 0)
			i++;
		trim = ft_strtrim(s[len], " \t");
		if (!ft_strlen(trim) || !ft_strncmp(trim, "\n", 1))
			return (free(trim), printf("Error\nWrong RGB values\n"), 1);
		free (trim);
		while (s[len][++i])
			if (!ft_isdigit(s[len][i]) && s[len][i] != ' '
			&& s[len][i] != '\t' && s[len][i] != '\n')
				return (printf("Error\nWrong RGB values\n"), 1);
	}
	return (0);
}

int	check_commas(char *str)
{
	int		i;
	char	*trim;

	i = 0;
	trim = ft_strtrim(str, " \t");
	while (trim[i])
	{
		if (trim[i + 1] && trim[i] == ',' && trim[i + 1] == ',')
			return (printf("Error\nWrong RGB format\n"), 1);
		i++;
	}
	free (trim);
	return (0);
}

int	check_colors(char *str, t_file *file, char c)
{
	char	**s;
	int		len;
	int		color;

	if (check_commas(str))
		return (1);
	s = ft_split(str, ',');
	len = 0;
	if (!s)
		return (perror("Error\nmalloc"), 1);
	while (s[len])
		len++;
	if (len != 3)
		return (printf("Error\nWrong RGB format\n"), 1);
	s[0] = update_red(s[0]);
	if (continue_checking_colors(s))
		return (1);
	len = -1;
	while (++len < 3)
		if (ft_atoi(s[len]) < 0 || ft_atoi(s[len]) > 255)
			return (printf("Error\nWrong RGB values\n"), 1);
	color = 0 << 24 | ft_atoi(s[0]) << 16 | ft_atoi(s[1]) << 8 | ft_atoi(s[2]);
	if (fill_ceilling(file, c, color))
		return (free_2d_array(s), 1);
	return (free_2d_array(s), 0);
}

int	check_elements(t_file *file, char **str)
{
	if (ft_strlen(str[0]) == 2 && str[0][0] != '1' && str[0][0] != '0')
	{
		if (ft_strncmp(str[0], "NO", 2) && ft_strncmp(str[0], "SO", 2)
			&& ft_strncmp(str[0], "WE", 2) && ft_strncmp(str[0], "EA", 2))
			return (printf("Error\nInvalid Id\n"), free_2d_array(str), 1);
		if (check_textures(str, file))
			return (free_2d_array(str), 1);
	}
	else if (ft_strlen(str[0]) == 1 && str[0][0] != '1' && str[0][0] != '0')
	{
		if (str[0][0] != 'C' && str[0][0] != 'F')
		{	
			if (str[0][0] == '\n')
			{
				ft_lstdelone(file->map, free);
				return (file->map = file->map->next, free_2d_array(str), 2);
			}
			return (printf("Error\nInvalid Id\n"), free_2d_array(str), 1);
		}
		if (check_colors((char *)file->map->content, file, str[0][0]))
			return (free_2d_array(str), 1);
	}
	else
		return (free_2d_array(str), 3);
	return (0);
}
