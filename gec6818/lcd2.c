#include "lcd2.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

static int fd = -1;
static int *plcd = NULL;

void lcd2_init()
{
	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		perror("open fb0 error");
		exit(1);
	}
	plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (plcd == MAP_FAILED)
	{
		perror("mmap lcd error");
		exit(1);
	}
	printf("lcd init success!\n");
}

void lcd2_draw_point(int x, int y, int color)
{
	*(plcd + 800 * y + x) = color;
}

void lcd2_draw_rgb888(char *rgb888, int width, int height, int x, int y)
{
	int i, j;
	char r, g, b;
	int color;
	char *p = rgb888;
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			color = r << 16 | g << 8 | b;
			lcd2_draw_point(j + x, i + y, color);
		}
	}
}

void lcd2_uninit()
{
	munmap(plcd, 800 * 480 * 4);
	close(fd);
	printf("lcd_uninit!\n");
}