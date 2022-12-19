
#include "Extern.h"
#include "Shader.h"
#include "Logger.h"

#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
using namespace Eigen;

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		Logger::error("Shader : file not successfully read");
		exit(0);
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	const int LOG_LEN = 512;
	unsigned int vertex, fragment;
	int success;
	char infoLog[LOG_LEN];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, LOG_LEN, nullptr, infoLog);
		Logger::error("Shader : vertex shader fail to compile\n" + string(infoLog));
		exit(0);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, LOG_LEN, nullptr, infoLog);
		Logger::error("Shader : fragment shader fail to compile\n" + string(infoLog));
		exit(0);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, LOG_LEN, nullptr, infoLog);
		Logger::error("Shader : program link failed\n" + string(infoLog));
		exit(0);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4f(const std::string& name, const Matrix4f& value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value.data());
}

void Shader::setVec3f(const std::string& name, float a, float b, float c) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), a, b, c);
}

void Shader::setVec3f(const std::string& name, const Vector3f& value) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value(0), value(1), value(2));
}

void Shader::setTexture(const std::string& name, TextureID texture, int rank) const {
	setInt(name, rank);
	glActiveTexture(GL_TEXTURE0 + rank);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::setColor(const std::string& name, Color color) const {
	setVec3f(name, color);
}