#pragma once
#include <memory>
#include <map>
#include <list>


class OpenGLScene;
class Drawable;
class IndexedVertexBuffer;
class ShaderProgram;
class OpenGLRenderer
{
    std::shared_ptr<ShaderProgram> m_program;
    std::list<
        std::pair<
        std::weak_ptr<IndexedVertexBuffer>, std::shared_ptr<Drawable>>> m_map;

public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    bool initialize();
    void resize(int w, int h);
	void update(int ms);
    void render(std::shared_ptr<OpenGLScene> scene);

private:
    std::shared_ptr<Drawable> getDrawable(
    std::shared_ptr<IndexedVertexBuffer> indexedVertexBuffer);
};

