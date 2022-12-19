#version 330
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNorm;
layout (location = 2) in vec2 vertTex;

out vec3 fragPos;
out vec3 fragNorm;
out vec2 fragTex;

uniform mat4 Model;
uniform mat4 ModelInv;
uniform mat4 View;
uniform mat4 Proj;

uniform mat4 lightTrans;

void fragPass() {
	fragPos = vec3(Model * vec4(vertPos, 1.0));
	fragNorm = vec3(transpose(ModelInv) * vec4(vertNorm, 1.0));
	fragTex = vertTex;
}

void main() {
	fragPass();
	gl_Position = Proj * View * vec4(fragPos, 1.0);
}