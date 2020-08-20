#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out VS_OUT {
	vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(Position, 1.0);
    gl_Position = vec4(Position, 1.0);
    vs_out.FragPos = vec3(model * vec4(Position, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model)))*Normal; // TODO: move to set uniform
    vs_out.TexCoord = TexCoord;
}
