#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} gs_in[];

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} gs_out;

vec3 GetNormal()
{
   //vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   //vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 a = vec3(gs_in[0].FragPos) - vec3(gs_in[1].FragPos);
   vec3 b = vec3(gs_in[2].FragPos) - vec3(gs_in[1].FragPos);
   return normalize(cross(a, b));
}  

void main() {
	//Normal = GetNormal();

    for(int i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        gs_out.FragPos = gs_in[i].FragPos;
        gs_out.Normal = gs_in[i].Normal;
        gs_out.TexCoord = gs_in[i].TexCoord;
        EmitVertex();
    }
    EndPrimitive();
}
