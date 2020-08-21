#include "demo.h"

#include <scene/ShaderOnlyScene.h>

Demo::Demo()
{

}

Demo::~Demo()
{
    for(Scene* scene : sceneList) {
        delete scene;
    }
}

Demo &Demo::instance()
{
    static Demo _instance;
    return _instance;
}

Scene* Demo::addScene()
{
    Scene* scene = new  ShaderOnlyScene();
    sceneList.push_back(scene);
    return scene;
}

Clip* Demo::addClip()
{
    clipList.push_back(Clip());
    return &clipList.back();
}

Clip *Demo::getClip(int id)
{
    return &clipList[id];
}

bool Demo::removeClips(int id, int count) {
    if(id+count < clipCount()) {
        clipList.erase(clipList.begin()+id, clipList.begin()+id+count);
        return true;
    }
    return false;
}

size_t Demo::clipCount() const
{
    return clipList.size();
}

bool Demo::swapClips(int idA, int idB)
{
    if(idA < clipCount() && idB < clipCount()) {
        Clip tmp = clipList[idA];
        clipList[idA] = clipList[idB];
        clipList[idB] = clipList[idA];
        return true;
    }
    return false;
}
