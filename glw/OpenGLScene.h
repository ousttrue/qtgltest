#pragma once
#include <memory>
#include <list>


class ICamera;
class IDrawable;
class OpenGLScene
{
    std::shared_ptr<ICamera> m_camera;
    std::list<std::shared_ptr<IDrawable>> m_drawables;

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    void render();

private:
};

