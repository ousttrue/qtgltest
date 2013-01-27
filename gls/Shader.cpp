#include "Shader.h"
#include <fstream>
#include <vector>


Shader::Shader()
: m_handle(0)
{
}


Shader::~Shader()
{
    if(m_handle){
        glDeleteShader(m_handle);
        m_handle=0;
    }
}


bool Shader::loadFile(GLenum shader_type, const char *path)
{
    m_handle=glCreateShader(shader_type);
    if(!m_handle){
        return false;
    }

    // read shader source
    std::ifstream io(path, std::ios::binary);
    if(!io){
        // error
        return false;
    }

    io.seekg (0, std::ios::end);
    int len = io.tellg ();
    if(len==0){
        // error
        return false;
    }
    io.seekg (false, std::ios::beg);

    std::vector<char> src(len);
    io.read (&src[0], src.size());


    // set source
    const GLchar *codeArray[]={
        &src[0],
    };
    const GLint codeSizeArray[]={
        static_cast<GLint>(src.size()),
    };
    glShaderSource(m_handle, 1, codeArray, codeSizeArray);

    // compile
    glCompileShader(m_handle);

    GLint result;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &result);
    return result!=GL_FALSE;
}

