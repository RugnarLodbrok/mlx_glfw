#include <stdlib.h>
#include <string.h>
#include "mlx.h"

t_mlx_image *mlx_new_image(t_mlx *mlx, int w, int h)
{
	t_mlx_image *im;

	im = calloc(1, sizeof(t_mlx_image));
	im->w = w;
	im->h = h;
	im->bpp = sizeof(unsigned int) * 8;
	im->data = malloc(sizeof(unsigned int) * w * h);
	return im;
}

unsigned int *mlx_get_data_addr(t_mlx_image *image, int *bpp, int *row_len, int *en)
{
	*bpp = image->bpp;
	*row_len = image->w * (image->bpp / 8);
	*en = 1234;
	return image->data;
}

void mlx_put_image_to_window(t_mlx *mlx, t_mlx_win *win, t_mlx_image *im, int x,
							 int y)
{
	int y1;
	int x1;
	int i;
	int j;
	int w;

	y1 = y + im->h;
	if (y1 > win->h)
		y1 = win->h;
	x1 = x + im->w;
	if (x1 > win->w)
		x1 = win->w;
	if (x1 <= x)
		return;
	w = x1 - x;
	for (i = y, j = 0; i < y1; i++, j++)
		memcpy(
				&win->fb.data[(win->h - 1 - i) * win->w + x],
				&im->data[im->w * j],
				w* sizeof(unsigned int));
}
