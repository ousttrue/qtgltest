#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "Cube.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include <glm/gtc/type_ptr.hpp>


OpenGLScene::OpenGLScene()
    : m_camera(new Camera)
{
    m_drawables.push_back(std::make_shared<Cube>());
}

OpenGLScene::~OpenGLScene()
{
}

bool OpenGLScene::initialize()
{
    for(auto it=m_drawables.begin(); it!=m_drawables.end(); ++it){
        (*it)->initialize();
    }
}

void OpenGLScene::update(int ms)
{
}

void OpenGLScene::render()
{
#if 0
    // fixed pipeline
    m_camera->apply();
    for(auto it=m_drawables.begin(); it!=m_drawables.end(); ++it){
        (*it)->draw();
    }
#else
    for(auto it=m_drawables.begin(); it!=m_drawables.end(); ++it){
        auto program=(*it)->getProgram();
        if(!program){
            return;
        }

        // shader
        glUseProgram(program->getHandle());
        // view
        program->setUniform("ProjectionMatrix", 
                glm::make_mat4(m_camera->getProjectionMatrix()));
        program->setUniform("ViewMatrix", 
                glm::make_mat4(m_camera->getViewMatrix()));
        //glm::make_mat4

        glBindVertexArray((*it)->getVAO()->getHandle());
        glDrawArrays(GL_TRIANGLES, 0, (*it)->getTriangleCount());
    }
#endif
}

