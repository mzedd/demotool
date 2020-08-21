#ifndef DEMO_H
#define DEMO_H

#include <scene/Scene.h>
#include <demo/Clip.h>

#include <vector>

class Demo
{
private:
    std::vector<Scene*> sceneList;
    std::vector<Clip> clipList;

    Demo();
    ~Demo();

public:
    Demo(const Demo&) = delete;
    Demo(Demo&&) = delete;
    Demo& operator=(const Demo&) = delete;
    Demo& operator=(Demo&&) = delete;

    static Demo& instance();

    Scene *addScene();

    Clip *addClip();
    Clip *getClip(int id);
    bool removeClips(int id, int count);
    size_t clipCount() const;
    bool swapClips(int idA, int idB);
};

#endif // DEMO_H
