#include "opengl.h"
#include "mlx.h"

static void fb_prepare_texture(t_mlx_win_framebuffer* fb)
{
	float vertices[] = {
			0, 0, 0, 0, 0,
			0, 1, 0, 0, 1,
			1, 1, 0, 1, 1,
			1, 0, 0, 1, 0};
	uint indices[] = {
			0, 1, 2,
			1, 2, 3};

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &fb->texo);
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb->w, fb->h,
				 0, GL_RGB, GL_UNSIGNED_BYTE, fb->data);

	glGenVertexArrays(1, &fb->vao);
	glGenBuffers(1, &fb->vbo);
	glBindVertexArray(fb->vao);
	glBindBuffer(GL_ARRAY_BUFFER, fb->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &fb->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fb->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void t_mlx_win_framebuffer_init(t_mlx_win_framebuffer* fb, int w, int h)
{
	fb->w = w;
	fb->h = h;
	fb->data = calloc(fb->w * fb->h, sizeof(uint));
	fb_prepare_texture(fb);

	fb->shader_program = link_shaders(
			2,
			make_shader(GL_VERTEX_SHADER, "shaders/vertex.glsl"),
			make_shader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl"));
}

void t_mlx_win_framebuffer_draw(t_mlx_win_framebuffer* fb)
{
	glUseProgram(fb->shader_program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glBindVertexArray(fb->vao);
	glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

/*
void t_mlx_win_init_fb(t_mlx_win* win)
{
	glGenTextures(1, &win->texo);
	glBindTexture(GL_TEXTURE_2D, win->texo);
	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA8,
			win->w, win->h, 0, GL_RGBA8,
			GL_UNSIGNED_BYTE, win->framebuffer);

	glGenFramebuffers(1, &win->read_fbo);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, win->read_fbo);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, win->texo, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void t_mlx_win_draw(t_mlx_win *win)
{
	glBindTexture(GL_TEXTURE_2D, win->texo);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, win->read_fbo);
	glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA8,
			win->w, win->h, 0, GL_RGBA8,
			GL_UNSIGNED_BYTE, win->framebuffer);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D, win->texo, 0);

//	glBindFramebuffer(GL_READ_FRAMEBUFFER, win->read_fbo);
	glBlitFramebuffer(0, 0, win->w, win->h,
					  0, 0, win->w, win->h,
					  GL_COLOR_BUFFER_BIT, GL_LINEAR);
//	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}
*/