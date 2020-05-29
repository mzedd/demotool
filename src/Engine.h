#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>

#include <GLFW/glfw3.h>
#include "scene/Camera.h"
#include "ShaderProgram.h"

constexpr int X_RATIO = 800;
constexpr int Y_RATIO = 600;

class Engine {
private:
    GLFWwindow* window;
    Camera camera;
    float deltaTime;
    float lastFrame;

    Engine();
    ~Engine();

    // glfw callbacks
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    std::vector<ShaderProgram> shaderList;

    static Engine& instance();

    int init(std::string windowName);
    void processInput();
    void update();
    bool run();
    Camera& getCamera();
    void addShader(ShaderProgram& shader);
	void updateShaderProjectionMatrices();
	unsigned int loadTexture(const char* path);
};

#endif /* ENGINE_H */
