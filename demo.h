#ifndef DEMO_H
#define DEMO_H

#include <QOpenGLShaderProgram>
#include "scene/Scene.h"
#include "demo/Clip.h"

#include <vector>

class Demo
{
private:
    std::vector<Scene> sceneList;
    std::vector<Clip> clipList;
    std::vector<QOpenGLShaderProgram*> shaderList;

    Demo();
    ~Demo();

public:
    Demo(const Demo&) = delete;
    Demo(Demo&&) = delete;
    Demo& operator=(const Demo&) = delete;
    Demo& operator=(Demo&&) = delete;

    static Demo& instance();

    Scene& addScene();
    void addScene(Scene scene);
    Scene* getScenePointer(int id);

    void addClip();
    Clip &getClip(int id);
    bool removeClips(int id, int count);
    const size_t clipCount() const;
    bool swapClips(int idA, int idB);

    QOpenGLShaderProgram *addShader(const QString &vertShaderFile, const QString& fragShaderFile);
    QOpenGLShaderProgram &getShaderProgram(int id);
};

#endif // DEMO_H
