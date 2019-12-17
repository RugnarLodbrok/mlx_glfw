#include <stdio.h>
#include "opengl.h"
#include "mlx.h"
#include "libft/mlx_consts.h"
#include "libft/libft.h"

void fps_meter_frame();

static void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	//todo: check if glfw gas normal key callbacks
}

static int t_mlx_win_create_window(t_mlx_win* win)
{
	win->window = glfwCreateWindow(win->w, win->h, "title", 0, 0);
	if (win->window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}
	glViewport(0, 0, win->w, win->h);
	return 0;
}

void t_mlx_win_init(t_mlx_win* win, int w, int h)
{
	ft_bzero(win, sizeof(t_mlx_win));

	win->w = w;
	win->h = h;
	if (t_mlx_win_create_window(win) < 0)
		ft_error_exit("failed to create window");
	t_mlx_win_framebuffer_init(&win->fb, w, h);
}

void mlx_pixel_put(t_mlx* mlx, t_mlx_win* win, int x, int y, unsigned int color)
{
	win->fb.data[win->w * y + x] = color;
}

void mlx()
{
	t_mlx_win win;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	t_mlx_win_init(&win, 800, 600);
	mlx_pixel_put(0, &win, 100, 100, 0xFFFFFF);
	mlx_pixel_put(0, &win, 101, 101, 0xFF0000);
	mlx_pixel_put(0, &win, 102, 102, 0x00FF00);
	mlx_pixel_put(0, &win, 103, 103, 0x0000FF);

	while (!glfwWindowShouldClose(win.window))
	{
		processInput(win.window);
		glfwSwapBuffers(win.window); //??
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		t_mlx_win_framebuffer_draw(&win.fb);
		glfwPollEvents();
		fps_meter_frame();
	}
	glfwTerminate();
}
