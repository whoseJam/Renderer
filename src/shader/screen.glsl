#version 330
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vnorm;
layout (location = 2) in vec2 vtex;

out vec2 ftex;

void main() {
	ftex = vtex;
	gl_Position = vec4(vpos.x, vpos.y, 0.0, 1.0);
}