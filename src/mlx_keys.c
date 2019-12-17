#include "string.h"
#include "mlx.h"
#include "mlx_consts.h"
#include "opengl.h"

int glut2mlx_keys[512];
int glut2mlx_mouse_buttons[8];

void mlx_init_glfw_key_map()
{
	memset(glut2mlx_keys, 0, 256);
	glut2mlx_keys[GLFW_KEY_ESCAPE] = KEY_ESC;
	glut2mlx_keys[GLFW_KEY_W] = KEY_W;
	glut2mlx_keys[GLFW_KEY_A] = KEY_A;
	glut2mlx_keys[GLFW_KEY_S] = KEY_S;
	glut2mlx_keys[GLFW_KEY_D] = KEY_D;
	glut2mlx_keys[GLFW_KEY_Q] = KEY_Q;
	glut2mlx_keys[GLFW_KEY_E] = KEY_E;
	glut2mlx_keys[GLFW_KEY_Z] = KEY_Z;
	glut2mlx_keys[GLFW_KEY_X] = KEY_X;
	glut2mlx_keys[GLFW_KEY_C] = KEY_C;
	glut2mlx_keys[GLFW_KEY_V] = KEY_V;
	glut2mlx_keys[GLFW_KEY_B] = KEY_B;
	glut2mlx_keys[GLFW_KEY_N] = KEY_N;
	glut2mlx_keys[GLFW_KEY_M] = KEY_M;
	glut2mlx_keys[GLFW_KEY_UP] = KEY_UP;
	glut2mlx_keys[GLFW_KEY_DOWN] = KEY_DOWN;
	glut2mlx_keys[GLFW_KEY_LEFT] = KEY_LEFT;
	glut2mlx_keys[GLFW_KEY_RIGHT] = KEY_RIGHT;
/*	glut2mlx_mouse_buttons[GLFW_LEFT_BUTTON] = MOUSE_B_LEFT;
	glut2mlx_mouse_buttons[GLFW_RIGHT_BUTTON] = MOUSE_B_RIGHT;
	glut2mlx_mouse_buttons[GLFW_MIDDLE_BUTTON] = MOUSE_B_MIDDLE;
	glut2mlx_mouse_buttons[GLFW_SCROLL_UP] = MOUSE_SCROLL_UP;
	glut2mlx_mouse_buttons[GLFW_SCROLL_DOWN] = MOUSE_SCROLL_DOWN;*/
}
