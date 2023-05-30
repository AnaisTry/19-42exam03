#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void  print_str(const char *s);
int ft_strlen(const char *s);
int ft_exit(FILE *file, char *map);

int	main(int argc, char **argv)
{
	FILE	*file = NULL;
	char	*map = NULL;
	int		count, width, height;
	char	c, type;
	float	x, y, r, dist;

    // check args
	if (argc != 2)
	{
		print_str("Error: argument\n");
		return (1);
	}

    // open file
	file = fopen(argv[1], "r");
	if (file == NULL)
		return(ft_exit(file, map));
    
    // read width, height, background char line
	count = fscanf(file, "%d %d %c\n", &width, &height, &c);
	if (count != 3 || width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_exit(file, map));

    // memorise the background
	map = calloc(width, height);
	if (!map)
		return (42);
	memset(map, c, width * height);

    // memorise foreground
	while (1)
	{
        // type of circle char, x_pos centre, y_pos centre, radius, foreground char
		count = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &r, &c);
		if (count == -1)
			break;	
		if (count != 5 || r <= 0.0f || (type != 'C' && type != 'c'))
			return(ft_exit(file, map));
		
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{	
				//ditance from center to upper left corner of char
				//srqt((Xa - Xb) * (Xa - Xb) + (Ya - Yb) * (Ya - Yb))
				dist = sqrtf((x - w) * (x - w) + (y - h) * (y - h));
				//draw the pixels of the circle  inside of radius 
				if (dist <= r)
					if (type == 'C' || dist > r - 1) //if full circle or at a distance within 1 of radius
						map[h * width + w] = c;
			}
		}
		//printf("%c %f %f %f %c\n", type, x, y, r, c);
	}

	// print map
	for (int h = 0; h < height; h++)
	{
		write(1, &map[h * width], width);
		print_str("\n");
	}

	// finish
	free(map);
	fclose(file);
	return(0);
}

int ft_strlen(const char *s)
{
	int len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	print_str(const char *s)
{
	write(1, s, ft_strlen(s));
}

int ft_exit(FILE *file, char *map)
{
	if (file)
		fclose(file);
	if (map)
		free(map);
	print_str("Error: Operation file corrupted\n");
	return (1);
}
