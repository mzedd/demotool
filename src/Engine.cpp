#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_header.h>

#include "Engine.h"

Engine::Engine() :
    window(nullptr),
    camera(Camera(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        2.5f)),
    deltaTime(0.0f),
    lastFrame(0.0f) {
}

Engine::~Engine() {
    glfwTerminate();
}

Engine& Engine::instance() {
    static Engine _instance;
    return _instance;
}

int Engine::init(std::string windowName) {
    // initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window
    window = glfwCreateWindow(X_RATIO, Y_RATIO, "FirstDemo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // configure glfw
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // set callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

     // configure OpenGL
    glViewport(0, 0, X_RATIO, Y_RATIO);
    glEnable(GL_DEPTH_TEST);

    return 0;
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Engine::instance().updateShaderProjectionMatrices();
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Engine::instance().getCamera().updateFront(static_cast<float>(xpos), static_cast<float>(ypos));
}

void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine::instance().getCamera().addScrollOffset(static_cast<float>(yoffset));
    Engine::instance().updateShaderProjectionMatrices();
}

void Engine::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += camera.speed * deltaTime * camera.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= camera.speed * deltaTime * camera.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= camera.speed * deltaTime * camera.getRight();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += camera.speed * deltaTime * camera.getRight();
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.position -= camera.speed * deltaTime * camera.getUp();
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.position += camera.speed * deltaTime * camera.getUp();
}

void Engine::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

bool Engine::run() {
    return !glfwWindowShouldClose(window);
}

Camera& Engine::getCamera() {
    return camera;
}

void Engine::addShader(ShaderProgram &shader) {
    shaderList.push_back(shader);
}

void Engine::updateShaderProjectionMatrices() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

    glm::mat4 projection = camera.getProjectionMatrix(width, height);

    for(std::vector<ShaderProgram>::iterator it = shaderList.begin(); it != shaderList.end(); ++it) {
       it->setMat4("projection", projection);
    }
}

unsigned int Engine::loadTexture(const char* path) { // TODO: integrate the correct way
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data) {
		GLenum format;
		switch (nrChannels) {
		case 1:
			format = GL_RED;	
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	return textureID;
}
