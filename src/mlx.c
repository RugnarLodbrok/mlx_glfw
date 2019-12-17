#include <stdio.h>
#include "opengl.h"
#include "mlx.h"
#include "mlx_consts.h"

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
	glfwSetWindowUserPointer(win->window, win);
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
	win->w = w;
	win->h = h;
	win->hooks = calloc(MLX_EVENTS_NUMBER, sizeof(t_mlx_hook));
	if (t_mlx_win_create_window(win) < 0)
	{
		printf("failed to create window\n");
		exit(1);
	}
	t_mlx_win_framebuffer_init(&win->fb, w, h);
}

void* mlx_new_window(t_mlx* mlx, int w, int h, const char* title)
{
	t_mlx_win* win;

	win = calloc(1, sizeof(t_mlx_win));
	mlx->win = win;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	t_mlx_win_init(win, w, h);
	return (win);
}

void* mlx_init()
{
	t_mlx* mlx;

	mlx = calloc(1, sizeof(t_mlx));
	mlx_init_glfw_key_map();
	return mlx;
}

void mlx_loop(t_mlx* mlx)
{
	t_mlx_win* win;

	win = mlx->win;
	while (!glfwWindowShouldClose(win->window))
	{
//		processInput(win->window);
		glfwSwapBuffers(win->window); //??
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		t_mlx_win_framebuffer_draw(&win->fb);
		if (mlx->loop_hook)
			mlx->loop_hook(mlx->loop_hook_p);
		glfwPollEvents();
		fps_meter_frame();
	}
	glfwTerminate();
}
