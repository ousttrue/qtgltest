#pragma once
#include <memory>
#include <list>


class Camera;
class IndexedVertexBuffer;
class ShaderProgram;
class OpenGLScene
{
    std::shared_ptr<Camera> m_camera;
    std::list<std::shared_ptr<IndexedVertexBuffer>> m_drawables;
    std::shared_ptr<ShaderProgram> m_program;

public:
    OpenGLScene();
    ~OpenGLScene();
    bool initialize();
    void update(int ms);
    void render();
};

