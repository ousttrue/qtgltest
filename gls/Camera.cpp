#include "Camera.h"
#include <array>
#include <algorithm>


Camera::Camera()
{
    std::array<float, 16> projection{
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f,
    };
    std::copy(projection.begin(), projection.end(), m_projection);

    std::array<float, 16> view{
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, 1.0f, 0,
        0, 0, 0, 1.0f,
    };
    std::copy(view.begin(), view.end(), m_view);
}

Camera::~Camera()
{
}

