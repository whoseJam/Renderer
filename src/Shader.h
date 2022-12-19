#pragma once

#include <iostream>

#include "Extern.h"
#include "Define.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float  value) const;
	void setMat4f(const std::string& name, const Eigen::Matrix4f& value) const;
	void setVec3f(const std::string& name, float x, float y, float z) const;
	void setVec3f(const std::string& name, const Eigen::Vector3f& value) const;
	void setTexture(const std::string& name, TextureID texture, int rank) const;
	void setColor(const std::string& name, Color value) const;
private:
	ShaderID ID;
};
