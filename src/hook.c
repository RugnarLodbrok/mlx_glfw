#include "mlx.h"
#include "mlx_consts.h"
#include "stdio.h"

extern int glut2mlx_keys[512];
extern int glut2mlx_mouse_buttons[8];

void mlx_loop_hook(t_mlx* mlx, int (* loop_hook)(void* p), void* p)
{
	mlx->loop_hook = loop_hook;
	mlx->loop_hook_p = p;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	t_mlx_win* win;
	t_mlx_hook* h;

	win = glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS)
		h = &win->hooks[MLX_EVENT_KEY_PRESS];
	else if (action == GLFW_RELEASE)
		h = &win->hooks[MLX_EVENT_KEY_RELEASE];
	else
		return;
//	if (action == GLFW_PRESS)
//		printf("press: %d `%c`\n", key, key);
	if (!h->f)
		return;
	h->f(glut2mlx_keys[key], h->p);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	t_mlx_win* win;
	t_mlx_hook* h;
	int x;
	int y;

	win = glfwGetWindowUserPointer(window);
	button = glut2mlx_mouse_buttons[button];
	if (action == GLFW_PRESS)
		h = &win->hooks[MLX_EVENT_MOUSE_PRESS];
	else if (action == GLFW_RELEASE)
		h = &win->hooks[MLX_EVENT_MOUSE_RELEASE];
	else
		return;
	printf("mouse\n");
	if (!h->f)
		return;
	x = 0;
	y = 0;
	h->f(button, x, y, h->p);
}


void mlx_hook(t_mlx_win* win, int event, int event_mask,
			  int (* hook)(),
			  void* p)
{
	t_mlx_hook* h;

	h = &win->hooks[event];
	h->f = hook;
	h->p = p;
	//todo: protection from calling twice?
	if (event == MLX_EVENT_KEY_PRESS || event == MLX_EVENT_KEY_RELEASE)
	{
		glfwSetKeyCallback(win->window, key_callback);
	}
	if (event == MLX_EVENT_MOUSE_RELEASE || event == MLX_EVENT_MOUSE_PRESS)
		glfwSetMouseButtonCallback(win->window, mouse_button_callback);
/*	if (event == MLX_EVENT_MOUSE_PRESS)
		if (!win->hooks[MLX_EVENT_MOUSE_RELEASE].f)
			glutMouseFunc(cb_mouse_event);
	if (event == MLX_EVENT_MOUSE_RELEASE)
		if (!win->hooks[MLX_EVENT_MOUSE_PRESS].f)
			glutMouseFunc(cb_mouse_event);
	if (event == MLX_EVENT_MOUSE_MOVE)
	{
		glutMotionFunc(cb_mouse_move);
		glutPassiveMotionFunc(cb_mouse_move);
	}
 */
}
