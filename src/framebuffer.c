#include "opengl.h"
#include "mlx.h"
#include <stb_image.h>

static void update_texture(t_mlx_win_framebuffer* fb, uint color)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb->w, fb->h,
				 0, GL_RGBA, GL_UNSIGNED_BYTE, fb->data);
}

static void fb_prepare_texture(t_mlx_win_framebuffer* fb)
{
	float vertices[] = {
			-1, -1, 0, 0, 1,
			-1, 1, 0, 0, 0,
			1, 1, 0, 1, 0,
			1, -1, 0, 1, 1};
	uint indices[] = {
			0, 1, 2,
			2, 3, 0};

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &fb->texo);
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	update_texture(fb, 0);

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
	glUniform1i(glGetUniformLocation(fb->shader_program, "tex"), 0);
}

void t_mlx_win_framebuffer_init(t_mlx_win_framebuffer* fb, int w, int h)
{
	fb->w = w;
	fb->h = h;
	fb->data = calloc(fb->w * fb->h, sizeof(uint));
	fb->shader_program = link_shaders(
			2,
			make_shader(GL_VERTEX_SHADER, "shaders/vertex.glsl"),
			make_shader(GL_FRAGMENT_SHADER, "shaders/fragment.glsl"));
	fb_prepare_texture(fb);
}

void t_mlx_win_framebuffer_draw(t_mlx_win_framebuffer* fb)
{
	update_texture(fb, 0);
	glUseProgram(fb->shader_program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fb->texo);
	glBindVertexArray(fb->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
