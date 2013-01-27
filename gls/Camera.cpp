#include "Camera.h"
#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <math.h>
#endif
#include <array>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



static float toRadian(float deglee)
{
    return static_cast<float>(M_PI * (deglee / 180.0f));
}


Camera::Camera()
    : m_headDeglee(0), m_pitchDeglee(0), m_distance(10.0f),
    m_fovy(30.0f), m_aspect(1.0f), m_near(0.5f), m_far(100.0f),
    m_shiftX(0), m_shiftY(0)
{
    calcViewMatrix();
    calcProjectionMatrix();
}

Camera::~Camera()
{
}

void Camera::resize(int w, int h)
{
    m_aspect=(float)w/(float)h;
    calcProjectionMatrix();
}

void Camera::head(float d)
{
    m_headDeglee+=d;
    calcViewMatrix();
}

void Camera::pitch(float d)
{
    m_pitchDeglee+=d;
    calcViewMatrix();
}

void Camera::dolly(int d)
{
    if(d<0){
        m_distance*=1.1f;
    }
    else{
        m_distance*=0.9f;
    }
    calcViewMatrix();
}

void Camera::shift(float x, float y)
{
    float FACTOR=0.5f;
    m_shiftX+=x * FACTOR * m_distance;
    m_shiftY+=y * FACTOR * m_distance;;
    calcViewMatrix();
}

void Camera::calcViewMatrix()
{
    glm::mat4 v(1.0f);
    v=glm::translate(v, glm::vec3(m_shiftX, m_shiftY, -m_distance));
    v=glm::rotate(v, toRadian(m_pitchDeglee), glm::vec3(1.0f, 0, 0));
    v=glm::rotate(v, toRadian(m_headDeglee), glm::vec3(0, 1.0f, 0));

    std::copy(&v[0][0], &v[0][0]+16, m_view);
}

void Camera::calcProjectionMatrix()
{
    glm::mat4 p = glm::perspective(m_fovy, m_aspect, m_near, m_far);
    std::copy(&p[0][0], &p[0][0]+16, m_projection);
}

