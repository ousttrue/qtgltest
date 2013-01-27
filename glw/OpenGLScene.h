#pragma once


class OpenGLScene
{
    unsigned int m_polyList;
    double m_projection[16];
    double m_view[16];

public:
    OpenGLScene();
    ~OpenGLScene();
    void update(int ms);
    void render();

private:
    void drawCube();
};

