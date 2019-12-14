#include <stdio.h>
#include "opengl.h"
#include "mlx.h"
#include "libft/mlx_consts.h"
#include "libft/libft.h"

void fps_meter_frame();

int t_mlx_win_create_window(t_mlx_win* win)
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
	win->framebuffer = calloc(w * h, sizeof(uint));
	if (t_mlx_win_create_window(win) < 0)
		ft_error_exit("failed to create window");
	glGenTextures(1, &win->texo);
	glBindTexture(GL_TEXTURE_2D, win->texo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA8, GL_UNSIGNED_BYTE, win->framebuffer);

	glGenFramebuffers(1, &win->read_fbo);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, win->read_fbo);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, win->texo, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void mlx()
{
	t_mlx_win win;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	t_mlx_win_init(&win, 800, 600);
	while (!glfwWindowShouldClose(win.window))
	{
//		processInput(window);
		glfwSwapBuffers(win.window); //??
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		fps_meter_frame();
	}
	glfwTerminate();
}
