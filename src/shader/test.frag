#version 330 core
out vec4 fcolor;
in vec3 fpos;
in vec3 fnorm;
in vec2 ftex;
in float fx;
in float fy;
in float fz;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shiness;
};

uniform Material material;

void main() {

	if (0 <= fx && fx <= 1 && 0 <= fy && fy <= 1) {
		fcolor = vec4(1, 0, 0, 1);
	}
	else if (0 <= fx && fx <= 1) {
		fcolor = vec4(0, 1, 0, 1);
	} 
	else if (0 <= fy && fy <= 1) {
		fcolor = vec4(0, 0, 1, 1.0);
	}
	else fcolor = vec4(1);


	fcolor = vec4(vec3(texture(material.diffuse, ftex)), 1.0);
}