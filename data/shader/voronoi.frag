#version 460 core

uniform vec2 iResolution;

void main(void)
{
    vec2 uv = gl_FragCoord.xy/iResolution;

    vec3 color = vec3(1.0);

    gl_FragColor = vec4(color*length(uv), 1.0);
}
