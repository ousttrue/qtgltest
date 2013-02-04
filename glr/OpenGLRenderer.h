#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>
#include <queue>

class OpenGLScene;
class Drawable;
class IndexedVertexBuffer;
class ShaderProgram;
class Camera;
class SceneNode;
class OpenGLRenderer
{
    std::shared_ptr<ShaderProgram> m_program;
    std::list<
        std::pair<
        std::weak_ptr<IndexedVertexBuffer>, std::shared_ptr<Drawable>>> m_map;
    std::queue<std::string> m_logQueue;

public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    bool initialize();
    void resize(int w, int h);
	void update(int ms);
    void render(std::shared_ptr<OpenGLScene> scene);
    bool hasLogMessage(){ return !m_logQueue.empty(); }
    std::string dequeueLogMessage();

private:
    std::shared_ptr<Drawable> getDrawable(
    std::shared_ptr<IndexedVertexBuffer> indexedVertexBuffer);
    void enqueueLogMessage(const std::string &log);
    void renderNode(std::shared_ptr<Camera> camera, std::shared_ptr<SceneNode> node);
};

