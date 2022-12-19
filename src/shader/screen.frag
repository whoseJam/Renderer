#version 330

out vec4 fcolor;

in vec2 ftex;

uniform sampler2D screenMap;
uniform int renderType;

uniform float far;
uniform float near;
uniform float depthDebugConst;

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
	if (renderType == 1) {
		vec3 col = texture(screenMap, ftex).rgb;
		fcolor = vec4(col, 1.0);
	} else {
		float depth = texture(screenMap, ftex).r;
		depth = LinearizeDepth(depth) / depthDebugConst;
		fcolor = vec4(vec3(depth), 1.0);
	}

}