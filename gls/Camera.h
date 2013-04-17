#pragma once
#include <memory>


class SceneNode;
class Camera
{
    // projection
    float m_fovy;
    float m_aspect;
    float m_near;
    float m_far;
    float m_projection[16];

    // view
    float m_headDeglee;
    float m_pitchDeglee;
    float m_distance;;
    float m_shiftX;
    float m_shiftY;
    float m_view[16];

    std::weak_ptr<SceneNode> m_node;

public:
    Camera(std::shared_ptr<SceneNode> node);
    ~Camera();
    // projection
    float *getProjectionMatrix(){ return m_projection; }
    void resize(int w, int h);

    // view
    float *getViewMatrix(){ return m_view; }
    void head(float d);
    void pitch(float d);
    void dolly(int d);
    void shift(float x, float y);

private:
    void calcViewMatrix();
    void calcProjectionMatrix();
};

