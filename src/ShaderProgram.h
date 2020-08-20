#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "Material.h"

enum class SHADER_TYPE {
	VERTEX_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER
};

class ShaderProgram {
public:
	unsigned int ID;

	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	ShaderProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, const bool value);
	void setInt(const std::string& name, const int value);
	void setFloat(const std::string& name, const float value);
	void setUniform(const std::string& name, const glm::vec2 vector);
    void setUniform(const std::string& name, const glm::vec3 vector);
    void setUniform(const std::string& name, const std::vector<glm::vec3>& vector);
    void setUniform(const std::string& name, const Material& material);
	void setMat4(const std::string& name, const glm::mat4& value) const;

private:
	unsigned int processShader(const char* shaderPath, const SHADER_TYPE type);
};

#endif /* SHADERPROGRAM_H */
