#ifndef MLX_H
# define MLX_H

#include "opengl.h"

# define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
# define MLX_FRAMERATE 60
# define MLX_FRAME_TIME_MS ((int)(1000. / MLX_FRAMERATE + .5))
# define GLUT_SCROLL_UP 3
# define GLUT_SCROLL_DOWN 4

# ifndef uint
#  define uint unsigned int
# endif

typedef struct
{
	void *p;
	int (*f)();
} t_mlx_hook;

typedef struct
{
	int w;
	int h;
	int bpp;
	unsigned int *data;
} t_mlx_image;

typedef struct
{
	int w;
	int h;
	uint *data;
	uint texo;
	uint rfbo;
} t_mlx_win_framebuffer;

typedef struct
{
	int w;
	int h;
	GLFWwindow *window;
	t_mlx_win_framebuffer fb;
	t_mlx_hook *hooks;
	GLuint read_fbo;
	GLuint texo;
} t_mlx_win;

typedef struct
{
	t_mlx_win *win;
	int (*loop_hook)(void *p);
	void *loop_hook_p;
} t_mlx;

void mlx_init_glfw_key_map();
void mlx_loop(t_mlx *mlx);
void mlx_init_glut_key_map();
void *mlx_new_window(t_mlx *mlx, int w, int h, const char *title);
void *mlx_init();
void mlx_pixel_put(t_mlx *mlx, t_mlx_win *win, int x, int y, unsigned int color);
void mlx_loop_hook(t_mlx *mlx, int (*loop_hook)(void *p), void *p);
void mlx_hook(t_mlx_win *win, int event, int event_mask,
			  int (*hook)(),
			  void *p);
void mlx_string_put(t_mlx *mlx, t_mlx_win *win, int x, int y, unsigned int color, const char *str);
t_mlx_image *mlx_new_image(t_mlx *mlx, int w, int h);
unsigned int *mlx_get_data_addr(t_mlx_image *image, int *bpp, int *row_len, int *en);
void mlx_put_image_to_window(t_mlx *mlx, t_mlx_win *win, t_mlx_image *im, int x, int y);

void t_mlx_win_framebuffer_init(t_mlx_win_framebuffer* fb, int w, int h);
void t_mlx_win_framebuffer_draw(t_mlx_win_framebuffer* fb);

#endif
