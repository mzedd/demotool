#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
	// load file and compile each shader
	unsigned int vertexShaderID = processShader(vertexPath, SHADER_TYPE::VERTEX_SHADER);
	unsigned int fragmentShaderID = processShader(fragmentPath, SHADER_TYPE::FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	// create and link shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	// print shader program linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders after linking
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char* geometryPath, const char* fragmentPath) {
	// load file and compile each shader
	unsigned int vertexShaderID = processShader(vertexPath, SHADER_TYPE::VERTEX_SHADER);
	unsigned int geometryShaderID = processShader(geometryPath, SHADER_TYPE::GEOMETRY_SHADER);
	unsigned int fragmentShaderID = processShader(fragmentPath, SHADER_TYPE::FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	// create and link shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, geometryShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	// print shader program linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders after linking
	glDeleteShader(vertexShaderID);
	glDeleteShader(geometryShaderID);
	glDeleteShader(fragmentShaderID);
}

unsigned int ShaderProgram::processShader(const char* shaderPath, const SHADER_TYPE type) {
	// retrieve the shader source code from filepath
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// open files
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// read file's buffer contents into stream
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const char* code = shaderCode.c_str();

	// 2. compile shader;
	unsigned int shaderID = 0;
	int success;
	char infoLog[512];

	// create and compile vertex shader
	switch (type) {
	case SHADER_TYPE::VERTEX_SHADER:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case SHADER_TYPE::GEOMETRY_SHADER:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case SHADER_TYPE::FRAGMENT_SHADER:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	
	glShaderSource(shaderID, 1, &code, NULL);
	glCompileShader(shaderID);

	// print compile errors if any
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}

void ShaderProgram::use() {
	glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, const bool value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, const int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, const float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec2 vector) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3 vector) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}

void ShaderProgram::setUniform(const std::string& name, const std::vector<glm::vec3>& vector) {
	for (int i = 0; i < vector.size(); i++) {
		setUniform(name + "[" + std::to_string(i) + "]", vector[i]);
	}
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string &name, const Material& material) {
    if(material.albedoTexture != 0) {
        setBool("material.albedoTexture", true);
        glBindTexture(GL_TEXTURE_2D, material.albedoTexture);
    } else {
        setBool("material.albedoTexture", false);
        setUniform("material.albedo", material.albedo);
    }
    setFloat("material.metallic", material.metallic);
    setFloat("material.roughness", material.roughness);
    setFloat("material.ao", material.ao);
}
