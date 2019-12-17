#include <fcntl.h>
#include "opengl.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"
//#include "shader.h"

char* read_file(char* f_name)
{
	int fd;
	t_arrayp a;
	int status;
	char* line;
	size_t total;
	int i;

	if ((fd = open(f_name, O_RDONLY)) < 0)
		ft_error_exit("can't open file %s", f_name);
	t_arrayp_init(&a);
	total = 0;
	while ((status = get_next_line(fd, &line)) > 0)
	{
		t_arrayp_push(&a, line);
		total += ft_strlen(line) + 1;
	}
	if (status < 0)
		ft_error_exit("can't read file %s", f_name); //todo: free
	close(fd);
	line = calloc(total + 1, sizeof(char));
	for (i = 0; i < a.count; ++i)
	{
		ft_strcat(line, a.data[i]);
		ft_strcat(line, "\n");
		free(a.data[i]);
	}
	t_arrayp_del(&a);
	return line;
}

uint make_shader(uint type, char* f_name)
{
	uint id;
	int success;
	char infoLog[512];
	char* source;

	source = read_file(f_name);
	id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		ft_error_exit("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",
					  infoLog);
	}
	free(source);
	return (id);
}

uint link_shaders(int n, ...)
{
	va_list ap;
	uint program;
	int i;
	int success;
	char infoLog[512];

	program = glCreateProgram();
			va_start(ap, n);
	for (i = 0; i < n; ++i)
		glAttachShader(program, va_arg(ap, uint));
			va_end(ap);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		ft_error_exit("ERROR::SHADER::LINKAGE_FAILURE\n%s\n", infoLog);
	}
			va_start(ap, n);
	for (i = 0; i < n; ++i)
		glDeleteShader(va_arg(ap, uint));
			va_end(ap);
	return program;
}
