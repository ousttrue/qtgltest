#pragma once
#include <memory>


class OpenGLScene;
class OpenGLRenderer
{
    std::shared_ptr<OpenGLScene> m_scene;

public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    void initialize();
    void resize(int w, int h);
	void update(int ms);
	void clear();
    void render();
};

