#include "string.h"
#include "mlx.h"
#include "mlx_consts.h"
#include "opengl.h"

int glfw2mlx_key_map[512];
int glfw2mlx_mouse_key_map[8];

void mlx_init_glfw_key_map()
{
	memset(glfw2mlx_key_map, 0, 256);
	glfw2mlx_key_map[GLFW_KEY_ESCAPE] = KEY_ESC;
	glfw2mlx_key_map[GLFW_KEY_W] = KEY_W;
	glfw2mlx_key_map[GLFW_KEY_A] = KEY_A;
	glfw2mlx_key_map[GLFW_KEY_S] = KEY_S;
	glfw2mlx_key_map[GLFW_KEY_D] = KEY_D;
	glfw2mlx_key_map[GLFW_KEY_Q] = KEY_Q;
	glfw2mlx_key_map[GLFW_KEY_E] = KEY_E;
	glfw2mlx_key_map[GLFW_KEY_Z] = KEY_Z;
	glfw2mlx_key_map[GLFW_KEY_X] = KEY_X;
	glfw2mlx_key_map[GLFW_KEY_C] = KEY_C;
	glfw2mlx_key_map[GLFW_KEY_V] = KEY_V;
	glfw2mlx_key_map[GLFW_KEY_B] = KEY_B;
	glfw2mlx_key_map[GLFW_KEY_N] = KEY_N;
	glfw2mlx_key_map[GLFW_KEY_M] = KEY_M;
	glfw2mlx_key_map[GLFW_KEY_UP] = KEY_UP;
	glfw2mlx_key_map[GLFW_KEY_DOWN] = KEY_DOWN;
	glfw2mlx_key_map[GLFW_KEY_LEFT] = KEY_LEFT;
	glfw2mlx_key_map[GLFW_KEY_RIGHT] = KEY_RIGHT;
	glfw2mlx_mouse_key_map[GLFW_MOUSE_BUTTON_1] = MOUSE_B_LEFT;
	glfw2mlx_mouse_key_map[GLFW_MOUSE_BUTTON_2] = MOUSE_B_RIGHT;
	glfw2mlx_mouse_key_map[GLFW_MOUSE_BUTTON_3] = MOUSE_B_MIDDLE;
}
