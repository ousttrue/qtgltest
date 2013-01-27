#pragma once
#include <GL/glew.h>
#include <string>
#include <queue>


class Shader
{
    GLuint m_handle;
    std::queue<std::string> m_logQueue;

public:
    Shader();
    ~Shader();
    GLuint getHandle()const{ return m_handle; }
    bool loadFile(GLenum shader_type, const char *path);

    bool hasLogMessage(){ return !m_logQueue.empty(); }
    std::string dequeueLogMessage();

private:
    void enqueueLogMessage(const std::string &log);
};

