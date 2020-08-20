#version 460 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} vs_in;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

void main() {
	vec3 color = vec3(1.0);

    vec3 lightDir   = normalize(lightPos - vs_in.FragPos);
    vec3 viewDir    = normalize(viewPos - vs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, vs_in.Normal);

	vec3 ambient  = material.ambient;
    vec3 diffuse  = material.diffuse*max(0.0, dot(vs_in.Normal, lightDir));
	vec3 specular = material.specular*pow(max(0.0, dot(viewDir, reflectDir)), material.shininess);

	color = (ambient + diffuse + specular)*lightColor;


    color = vec3(1.0f, 0.0f, 0.0f);

	FragColor = vec4(color, 1.0);
}
