#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"
#include "SceneNode.h"


OpenGLScene::OpenGLScene()
    : m_camera(new Camera), m_root(new SceneNode("__root__")),
    m_w(1), m_h(1),
    m_mouseLeft(false), m_mouseMiddle(false), m_mouseRight(false),
    m_mouseX(0), m_mouseY(0)
{
    m_root->addChild("triangle", IndexedVertexBuffer::CreateTriangle());
    //m_drawables.push_back(IndexedVertexBuffer::CreateCube(0.5f));
}

OpenGLScene::~OpenGLScene()
{
}

void OpenGLScene::update(int ms)
{
}

void OpenGLScene::resize(int w, int h)
{
    m_w=w;
    m_h=h;
    m_camera->resize(w, h);
}

void OpenGLScene::clear()
{
    m_root->clear();
}

bool OpenGLScene::onMouseLeftDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseLeft=true;
    return false;
}

bool OpenGLScene::onMouseMiddleDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseMiddle=true;
    return false;
}

bool OpenGLScene::onMouseRightDown(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseRight=true;
    return false;
}

bool OpenGLScene::onMouseLeftUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseLeft=false;
    return false;
}

bool OpenGLScene::onMouseMiddleUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseMiddle=false;
    return false;
}

bool OpenGLScene::onMouseRightUp(int x, int y)
{
    m_mouseX=x;
    m_mouseY=y;
    m_mouseRight=false;
    return false;
}

bool OpenGLScene::onMouseMove(int x, int y)
{
    bool repaint=false;
    int dx=x-m_mouseX;
    int dy=y-m_mouseY;
    m_mouseX=x;
    m_mouseY=y;
    if(m_mouseLeft){
    }
    if(m_mouseMiddle){
        float min=m_w<m_h ? m_w : m_h;
        float ratio=1.0f/min;
        m_camera->shift(dx*ratio, -dy*ratio);
        repaint=true;
    }
    if(m_mouseRight){
        float min=m_w<m_h ? m_w : m_h;
        float ratio=14000.0f/min;
        m_camera->head(dx*ratio);
        m_camera->pitch(dy*ratio);
        repaint=true;
    }
    return repaint;
}

bool OpenGLScene::onMouseWheel(int d)
{
    m_camera->dolly(d);
    return true;
}

