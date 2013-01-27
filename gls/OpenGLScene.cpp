#include "OpenGLScene.h"
#include <GL/glew.h>
#include "Camera.h"
#include "IndexedVertexBuffer.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>


OpenGLScene::OpenGLScene()
    : m_camera(new Camera)
{
    m_drawables.push_back(IndexedVertexBuffer::CreateTriangle());
}

OpenGLScene::~OpenGLScene()
{
}

static std::shared_ptr<Shader> loadShader(GLenum shader_type, const char *path)
{
    auto shader=std::make_shared<Shader>();
    if(!shader->loadFile(shader_type, path)){
        return std::shared_ptr<Shader>();
    }
    return shader;
}

bool OpenGLScene::initialize()
{
    auto vert=loadShader(GL_VERTEX_SHADER, "basic.vert");
    if(!vert){
        // fatal
        return false;
    }

    auto frag=loadShader(GL_FRAGMENT_SHADER, "basic.frag");
    if(!frag){
        // fatal
        return false;
    }

    m_program=std::make_shared<ShaderProgram>();
    if(!m_program->link(vert, frag)){
        // fatal
        return false;
    }

    for(auto it=m_drawables.begin(); it!=m_drawables.end(); ++it){
        (*it)->setShader(m_program);
        (*it)->initialize();
    }
}

void OpenGLScene::update(int ms)
{
}

void OpenGLScene::render()
{
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

        // set vertex buffer
        glBindVertexArray((*it)->getVAO()->getHandle());
        // set index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*it)->getVAO()->getIndexHandle());

        // draw each submesh
        unsigned int offset=0;
        int submeshCount=(*it)->getSubMeshCount();
        for(int i=0; i<submeshCount; ++i){
            unsigned int indexCount=(*it)->getIndexCount(i);
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 
                    (const GLvoid*)offset);
            offset+=indexCount;
        }
    }
}

