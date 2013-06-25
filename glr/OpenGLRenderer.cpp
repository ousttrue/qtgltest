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
#include "Light.h"
#include "VAO.h"
#include "IndexedVertexBuffer.h"
#include "Shader.h"
#include "SceneNode.h"
#include <algorithm>


OpenGLRenderer::OpenGLRenderer()
{
}


OpenGLRenderer::~OpenGLRenderer()
{
}

bool OpenGLRenderer::initialize()
{
	GLenum err=glewInit();
	if(err!=GLEW_OK){
		// fatal
        enqueueLogMessage("fail to glewInit");
        return false;
	}

    // OpenGL settigns
    glEnable(GL_DEPTH_TEST);

    // init shader
    auto vert=std::make_shared<Shader>();
    if(!vert->loadFile(GL_VERTEX_SHADER, "basic.vert")){
        enqueueLogMessage("basic.vert");
        while(vert->hasLogMessage()){
            enqueueLogMessage(vert->dequeueLogMessage());
        }
        return false;
    }

    auto frag=std::make_shared<Shader>();
    if(!frag->loadFile(GL_FRAGMENT_SHADER, "basic.frag")){
        enqueueLogMessage("basic.frag");
        while(frag->hasLogMessage()){
            enqueueLogMessage(frag->dequeueLogMessage());
        }
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

    renderNode(scene->getCameraNode(), scene->getLightNode(), scene->getRootNode());

    glFlush();
}

void OpenGLRenderer::renderNode(std::shared_ptr<SceneNode> cameraNode, 
        std::shared_ptr<SceneNode> lightNode,
        std::shared_ptr<SceneNode> node)
{
    auto camera=cameraNode->getCamera();
    if(!camera){
        return;
    }
    auto light=lightNode->getLight();

    auto buffer=node->getMesh();
    if(buffer){
        auto drawable=getDrawable(buffer);
        auto program=drawable->getProgram();
        if(program){

            // shader
            glUseProgram(program->getHandle());

            // matrices
            glm::mat4 projection=glm::make_mat4(camera->getProjectionMatrix());
            program->setUniform("ProjectionMatrix", projection);
            glm::mat4 mv=glm::make_mat4(camera->getViewMatrix());
            program->setUniform("ModelViewMatrix", mv);
            program->setUniform("NormalMatrix", glm::mat3(mv));
            program->setUniform("MVP",  projection * mv);

            // light
            program->setUniform("Ld", glm::vec3(
                        light->getDiffuse().x,
                        light->getDiffuse().y,
                        light->getDiffuse().z
                        ));
            auto &lightPos=lightNode->position();
            program->setUniform("LightPosition", glm::vec4(lightPos[0], lightPos[1], lightPos[2], 1.0f));

            // set vertex buffer
            glBindVertexArray(drawable->getVAO()->getHandle());
            // set index buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable->getVAO()->getIndexHandle());

            // draw each submesh
            unsigned int offset=0;
            int submeshCount=buffer->getSubMeshCount();
            for(int i=0; i<submeshCount; ++i){
                // submesh
                auto &material=buffer->getMaterial(i);
				program->setUniform("Kd", glm::vec3(
					material.diffuse.x, 
					material.diffuse.y, 
					material.diffuse.z
					));
                glDrawElements(GL_TRIANGLES, material.index_count, GL_UNSIGNED_INT, 
                        (const GLvoid*)(offset * sizeof(GLuint)));
				offset+=material.index_count;
            }
        }
    }

    for(auto it=node->begin(); it!=node->end(); ++it){
        renderNode(cameraNode, lightNode, *it);
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

std::string OpenGLRenderer::dequeueLogMessage()
{
    std::string log=m_logQueue.front();
    m_logQueue.pop();
    return log;
}

void OpenGLRenderer::enqueueLogMessage(const std::string &log)
{
    m_logQueue.push(log);
}

