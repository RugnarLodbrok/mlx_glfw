#include "mlx.h"
#include "mlx_consts.h"
#include <stdio.h>

static int loop_hook(void *p)
{
	static int i = 1;

	if (i)
	{
		printf("loop hook works!\n");
		i = 0;
	}
	return (0);
}

static int key_down_f(int keycode, void *p)
{
	if (keycode == KEY_ESC)
		exit(0);
	printf("key down: %d\n", keycode);
	return (0);
}

static int mouse_press_f(int button, int x, int y, void *p)
{
	printf("CLICK CALLBACK %d %d\n", x, y);
	return (0);
}

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "HELLO MLX");
	mlx_pixel_put(mlx, win, 100, 100, 0xFFFFFF);
	mlx_pixel_put(mlx, win, 101, 101, 0xFF0000);
	mlx_pixel_put(mlx, win, 102, 102, 0x00FF00);
	mlx_pixel_put(mlx, win, 103, 103, 0x0000FF);
	mlx_loop_hook(mlx, loop_hook, 0);
	mlx_hook(win, MLX_EVENT_KEY_PRESS, 0, key_down_f, 0);
	mlx_hook(win, MLX_EVENT_MOUSE_PRESS, 0, mouse_press_f, 0);
	mlx_loop(mlx);
	return 0;
}
