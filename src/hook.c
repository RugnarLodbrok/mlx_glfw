#include "mlx.h"
#include "mlx_consts.h"
#include "stdio.h"

extern int glfw2mlx_key_map[512];
extern int glfw2mlx_mouse_key_map[8];

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
	if (!h->f)
		return;
	h->f(glfw2mlx_key_map[key], h->p);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	t_mlx_win* win;
	t_mlx_hook* h;
	double x;
	double y;

	win = glfwGetWindowUserPointer(window);
	button = glfw2mlx_mouse_key_map[button];
	if (action == GLFW_PRESS)
		h = &win->hooks[MLX_EVENT_MOUSE_PRESS];
	else if (action == GLFW_RELEASE)
		h = &win->hooks[MLX_EVENT_MOUSE_RELEASE];
	else
		return;
	printf("mouse\n");
	if (!h->f)
		return;
	glfwGetCursorPos(window, &x, &y);
	h->f(button, (int)x, (int)y, h->p);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	t_mlx_win* win;
	t_mlx_hook* h;
	double x;
	double y;

	win = glfwGetWindowUserPointer(window);
	h = &win->hooks[MLX_EVENT_MOUSE_PRESS];
	if (!h->f)
		return;
	glfwGetCursorPos(window, &x, &y);
	if (xoffset)
	{
		if (xoffset < 0)
			h->f(MOUSE_SCROLL_UP, (int)x, (int)y, h->p);
		else
			h->f(MOUSE_SCROLL_DOWN, (int)x, (int)y, h->p);
	}
	if (yoffset)
	{
		if (yoffset < 0)
			h->f(MOUSE_SCROLL_LEFT, (int)x, (int)y, h->p);
		else
			h->f(MOUSE_SCROLL_RIGHT, (int)x, (int)y, h->p);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	t_mlx_win* win;
	t_mlx_hook* h;

	win = glfwGetWindowUserPointer(window);
	h = &win->hooks[MLX_EVENT_MOUSE_MOVE];
	if (h->f)
		h->f((int)xpos, (int)ypos, h->p);
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
		glfwSetKeyCallback(win->window, key_callback);
	if (event == MLX_EVENT_MOUSE_RELEASE || event == MLX_EVENT_MOUSE_PRESS)
		glfwSetMouseButtonCallback(win->window, mouse_button_callback);
	if (event == MLX_EVENT_MOUSE_PRESS)
		glfwSetScrollCallback(win->window, scroll_callback);
	if (event == MLX_EVENT_MOUSE_MOVE)
		glfwSetCursorPosCallback(win->window, cursor_position_callback);
}
