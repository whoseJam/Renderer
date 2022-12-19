#version 330
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vnorm;
layout (location = 2) in vec2 vtex;

out vec3 fpos;
out vec3 fnorm;
out vec2 ftex;
out float fx;
out float fy;
out float fz;

uniform mat4 model;
uniform mat4 modelInv;
uniform mat4 view;
uniform mat4 projection;
uniform float far;
uniform float near;
uniform float maxX;
uniform float minX;
uniform float maxY;
uniform float minY;

void main() {
	fpos = vec3(model * vec4(vpos, 1.0));
	fnorm = vnorm;
	ftex = vtex;
	vec4 viewPos = view * vec4(fpos, 1.0);
	float z = viewPos.z;
	float x = viewPos.x * near / abs(z);
	float y = viewPos.y * near / abs(z);

	vec4 tmp = projection * viewPos;
	float proj_x = tmp.x;
	float proj_y = tmp.y;
	float proj_z = tmp.z;
	
	//x = x * 2.0 / (maxX - minX);
	//y = y * 2.0 / (maxY - minY);
	x = 2.0 * (x - minX) / (maxX - minX) - 1;
	y = 2.0 * (y - minY) / (maxY - minY) - 1;
	z = (z + 0.01 - near) / (far - near);
	
	gl_Position = 
	//projection * viewPos;
	vec4(x * tmp.w, y * tmp.w, z * tmp.w, tmp.w);
	//vec4(proj_x, proj_y, proj_z, tmp.w);
}