#pragma once


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
    float m_view[16];

public:
    Camera();
    ~Camera();
    // projection
    float *getProjectionMatrix()/*override*/{ return m_projection; }
    void resize(int w, int h);

    // view
    float *getViewMatrix()/*override*/{ return m_view; }
    void head(float d);
    void pitch(float d);
    void dolly(int d);

private:
    void calcViewMatrix();
    void calcProjectionMatrix();
};

