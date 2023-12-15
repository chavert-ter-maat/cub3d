#include "../../include/cubed.h"

void	get_start_pos(t_cubed *cubed)
{
	int	x;
	int y;

	y = 0;
	while (cubed->map[y])
	{
		x = 0;
		while (cubed->map[y][x])
		{
			if (cubed->map[y][x] == 'N' || cubed->map[y][x] == 'Z' ||
				cubed->map[y][x] == 'E' || cubed->map[y][x] == 'W')
			{
				cubed->start_pos[0] = x;
				cubed->start_pos[1] = y;
				return ;
			}
			x++;
		}
		y++;
	}
	perror("start position not found");
	exit (EXIT_FAILURE);
}

char **copy_map(char **file, int start, int end, int index)
{
	char **map;
	int	strlen;

	map = malloc(((end - start) + 1) * sizeof(char*));
	if (!map)
	{
		perror("Malloc failed in copy_map #1\n");
		exit(EXIT_FAILURE);
	}
	map[end - start] = NULL;
    while (start < end)
    {
        strlen = ft_strlen(file[start]);
        map[index] = malloc((strlen + 1) * sizeof(char));
        if (!map[index])
        {
			perror("Malloc failed in copy_map #2\n");
            exit(EXIT_FAILURE);
        }
        ft_strlcpy(map[index], file[start], strlen); // TODO: protect?
        start++;
        index++;
    }
	return (map);
}

int	find_start_map(char **file)
{
	int i;
	int j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while(file[i])
	{
		j = 0;
		while(file[i][j] == '1' || file[i][j] == ' ')
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

void	parse_map(t_cubed *cubed, char **file)
{
	char	**map;
	int		start;
	int 	end;
	int		norminette_intje;
	
	end = 0;
	norminette_intje = 0;
	start = find_start_map(file);
	while(file[end])
		end++;
	map = copy_map(file, start, end, norminette_intje);
	cubed->map = map;
}

