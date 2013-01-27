#pragma once
#include <memory>
#include <list>


class ICamera;
class IDrawable;
class ShaderProgram;
class OpenGLScene
{
    std::shared_ptr<ICamera> m_camera;
    std::list<std::shared_ptr<IDrawable>> m_drawables;
    std::shared_ptr<ShaderProgram> m_program;

public:
    OpenGLScene();
    ~OpenGLScene();
    bool initialize();
    void update(int ms);
    void render();
};

