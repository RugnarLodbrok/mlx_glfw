#include "opengl.h"
#include "mlx.h"
#include <stb_image.h>

void t_mlx_win_framebuffer_init(t_mlx_win_framebuffer* fb, int w, int h)
{
	fb->w = w;
	fb->h = h;
	fb->data = calloc(fb->w * fb->h, sizeof(uint));

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &fb->texo);
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &fb->rfbo);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fb->rfbo);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, fb->texo, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void t_mlx_win_framebuffer_draw(t_mlx_win_framebuffer* fb)
{
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb->w, fb->h,
				 0, GL_RGBA, GL_UNSIGNED_BYTE, fb->data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, fb->rfbo);
	glBlitFramebuffer(0, 0, fb->w, fb->h,
					  0, 0, fb->w, fb->h,
					  GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}
