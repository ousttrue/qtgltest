#include "OpenGLRenderer.h"
#include "OpenGLScene.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include "Drawable.h"
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "VAO.h"
#include "IndexedVertexBuffer.h"
#include "Shader.h"
#include <algorithm>


OpenGLRenderer::OpenGLRenderer()
{
}


OpenGLRenderer::~OpenGLRenderer()
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


bool OpenGLRenderer::initialize()
{
	GLenum err=glewInit();
	if(err!=GLEW_OK){
		// fatal
        return false;
	}

    // OpenGL settigns
    glEnable(GL_DEPTH_TEST);

    // init shader
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

    return true;
}


void OpenGLRenderer::resize(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


void OpenGLRenderer::render(std::shared_ptr<OpenGLScene> scene)
{
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    auto camera=scene->getCamera();

    for(auto it=scene->begin(); it!=scene->end(); ++it){

        auto drawable=getDrawable(*it);

        auto program=m_program;
        if(!program){
            return;
        }

        // shader
        glUseProgram(program->getHandle());
        // view
        program->setUniform("ProjectionMatrix", 
                glm::make_mat4(camera->getProjectionMatrix()));
        program->setUniform("ViewMatrix", 
                glm::make_mat4(camera->getViewMatrix()));

        // set vertex buffer
        glBindVertexArray(drawable->getVAO()->getHandle());
        // set index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->getVAO()->getIndexHandle());

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


std::shared_ptr<Drawable> OpenGLRenderer::getDrawable(
        std::shared_ptr<IndexedVertexBuffer> indexedVertexBuffer)
{
    auto found=std::find_if(m_map.begin(), m_map.end(), [indexedVertexBuffer](
                std::pair<
                std::weak_ptr<IndexedVertexBuffer>, 
                std::shared_ptr<Drawable>
                > pair){

                return pair.first.lock()==indexedVertexBuffer;

            });
    if(found!=m_map.end()){
        return found->second;
    }

    auto drawable=std::make_shared<Drawable>();

    drawable->setShader(m_program);
    drawable->initialize(indexedVertexBuffer);

    m_map.push_back(std::make_pair(indexedVertexBuffer, drawable));
    return drawable;
}

