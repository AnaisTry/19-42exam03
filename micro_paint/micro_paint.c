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
	float	x, y, r_w, r_h;
	
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
	count = fscanf(file, "%i %i %c\n", &width, &height, &c);
	if (count !=3 || width <= 0 || width > 300 || height <= 0 || height > 300)
		return(ft_exit(file, map));

	// memorise the background
	map = calloc(width, height);
	if (!map)
		return (1);
	memset(map, c, width * height);
	
	// memorise foreground  
	while (1)
	{
	        // type of rectangle char, x_pos pix, y_pos pix, width, height, foreground char
		count = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &r_w, &r_h, &c);
		// break or exit if EOF or instructions not conform
		if (count == -1)
			break;
		if (count != 6 || (type != 'R' && type != 'r') || r_w <= 0.0f || r_h <= 0.0f)
			return(ft_exit(file, map)); 
		// get the coords of the last corner of rectangle : max width and max height
		r_w += x;
		r_h += y;
		// nested loop
		for (int h = 0; h < height ;h++)
		{	
			for (int w = 0; w < width; w++)
			{
				// if within the limits of the rectangle
                if (w <= r_w && w >= x && h <= r_h && h >= y)
					if (type == 'R' || w > r_w - 1 || w < x + 1 || h > r_h - 1 || h < y + 1)//if it's a filled rectangle or a point within the limits of the pix cords + 1 and the last point -1 : overwright with foreground char
                        map[h * width + w] = c;
        	}           
		}	
	}
	
	// print map
	for (int h = 0; h < height; h++)
	{
		write (1, &map[h * width], width);
		print_str("\n");
	}

	// finish
	free(map);
	fclose(file);
	return (0);
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
