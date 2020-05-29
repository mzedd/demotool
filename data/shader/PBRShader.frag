#version 460 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} fs_in;

const float PI = acos(-1.0);

struct Material {
    vec3 albedo;
    bool albedoTexture;
	float metallic;
	float roughness;
	float ao;
};

struct LightSource {
    uint type;
    vec3 intensity;
    vec3 position;
    vec3 direction;
};

uniform vec3 camPos;
uniform int lightCount;
uniform LightSource lightSource[1];
uniform Material material;
uniform sampler2D texture1;

out vec4 FragColor;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness * roughness;
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, V), 0.0);
	float ggx2  = GeometrySchlickGGX(NdotV, roughness);
	float ggx1  = GeometrySchlickGGX(NdotL, roughness);

	return ggx1 * ggx2;
}

void main() {
    vec3 albedo;
    if(material.albedoTexture) {
        albedo = texture(texture1, 5.0*fs_in.TexCoord).xyz;
    } else {
        albedo = material.albedo;
    }

    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(camPos - fs_in.FragPos);
	
	vec3 F0 = vec3(0.04); // assumption from metallic workflow
    F0 = mix(F0, albedo, material.metallic);

	vec3 Lo = vec3(0.0);
	for(int i = 0; i < lightCount; i++) {
		// calculate per-light radiance
        vec3 L = normalize(lightSource[i].position - fs_in.FragPos);
		vec3 H = normalize(V + L);
        float distance = length(lightSource[i].position - fs_in.FragPos);
		float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightSource[i].intensity * attenuation;

		// cook-torrance brdf
		float NDF = DistributionGGX(N, H, material.roughness);
		float G = GeometrySmith(N, V, L, material.roughness);
		vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

		vec3 kS = F; // ratio of reflection
		vec3 kD = vec3(1.0) - kS; // ratio of recfraction
		kD *= 1.0 - material.metallic; // if surface gets more metallic reduce refraction

		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular = numerator / max(denominator, 0.001);

		// add to outgoing radiance Lo
		float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}

    vec3 ambient = vec3(0.03) * albedo * material.ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0)); // HDR to LDR correction
	color = pow(color, vec3(1.0 / 2.2)); // gamma correction

    FragColor = vec4(color, 1.0);
}
