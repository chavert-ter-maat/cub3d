#include "../../include/cubed.h"

static char	**create_map(t_cubed *cubed)
{
    int y;
    char **map;

    y = 0;
	printf("%i = total_row + 1\n", cubed->total_row + 1 );
    map = ft_calloc((cubed->total_row + 1), sizeof(char*));
    if (!map)
        return (NULL);
    while (y < cubed->total_row)
    {
        map[y] = ft_calloc((cubed->max_column + 1), sizeof(char));
        if (!map[y])
        {
            while (--y >= 0)
                free(map[y]);
            free(map);
            return (NULL);
        }
		map[y][cubed->max_column + 1] = '\0';
        y++;
    }
	printf("%i = y\n", y);
	map[y] = NULL;
    return (map);
}

void	copy_map(t_cubed *cubed, char **map, int start, int end)
{
	int		index;

	index = 0;
	while (start < end)
	{
		ft_strlcpy(map[index], cubed->file[start], cubed->max_column + 1);
		start++;
		index++;
	}
}

static int	find_start_end(char **file, int i)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == '1' || file[i][j] == ' ' || file[i][j] == '	') // todo: isspace
			j++;
		if (file[i][j] == '\0')
		{
			start = i;
			break ;
		}
		i++;
	}
	return (start);
}

int	find_max_width(t_cubed *cubed, int start, int end)
{
	int	i;
	int max_i;

	i = 0;
	max_i = 0;
	while (start < end)
	{
		i = 0;
		while (cubed->file[start][i])
			i++;
		if (i >= max_i)
			max_i = i;
		start++;
	}
	cubed->max_column = max_i;
	printf("%i = cubed->max_column\n", cubed->max_column);
	if (cubed->max_column == 0)
	{
		ft_printf("Error: Incorrect map\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_map(t_cubed *cubed)
{
	int	start;
	int	end;

	end = 0;
	start = find_start_end(cubed->file, 0);
	if (start == 0)
		return (FAILURE);
	end = find_start_end(cubed->file, start + 1) + 1;
	if (cubed->file[end] != NULL)
		return (FAILURE);
	cubed->total_row = end - start;
	printf("%i = cubed->total_row\n", cubed->total_row);
	if (find_max_width(cubed, start, end) == FAILURE)
		return (FAILURE);
	cubed->map = create_map(cubed);
	if (cubed->map == NULL)
		return (FAILURE);
	cubed->map_val = create_map(cubed);
	if (cubed->map_val == NULL)
	{
		free_2d_array(cubed->map);
		return (FAILURE);
	}
	copy_map(cubed, cubed->map, start, end);
	copy_map(cubed, cubed->map_val, start, end);
	return (SUCCESS);
}
