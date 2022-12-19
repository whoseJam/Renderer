#version 330 core
out vec4 fragColor;
in vec3 fragPos;
in vec3 fragNorm;
in vec2 fragTex;

struct _Material {
	vec3 albedo;
	sampler2D albedoTexture;
	float metallic;
	sampler2D metallicTexture;
	float roughness;
};

struct _PointLight {
	vec3 position;
};

uniform _Material Material;
uniform _PointLight PointLight;
uniform vec3 ViewPos;

float DNorm(float rough, float cosThetaH) {
	float A = rough * rough;
	float B = cosThetaH * cosThetaH;
	float C = A - 1;
	float D = B * C + 1;
	float E = D * D * 3.14159;
	float F = A / E;
	return F;
}

float Gs_GGX(float rough, float cosTheta) {
	float k = (rough + 1) * (rough + 1) / 3.0;
	float A = cosTheta / (k + (1 - k) * cosTheta);
	return A;
}

float Visibility() {
	return 1.0;
}

vec3 fBRDF() {
	vec3 lightDir = normalize(PointLight.position - fragPos);
	vec3 viewDir = normalize(ViewPos - fragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float cosThetaH = dot(fragNorm, halfDir);
	float cosThetaL = dot(fragNorm, lightDir);

	vec3 F0 = vec3(0.04);
	float metallic = Material.metallic;
	float rough = Material.roughness;
	vec3 kDiff = (vec3(1.0) - F0) * (1 - metallic);
	vec3 kSpec = F0;
	vec3 cDiff = Material.albedo;
	float cSpec = DNorm(rough, cosThetaH);
	return kDiff * cDiff + kSpec * cSpec;
}

void main() {
	fragColor = vec4(fBRDF(), 1);
}