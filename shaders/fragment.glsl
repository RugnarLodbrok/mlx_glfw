#version 460 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
    //    FragColor = texture(tex, TexCoord);
    FragColor = vec4(1., 1., 1., 1.);
}
