#include "Camera.h"

Camera::Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldUP)
{
    m_position = position;
    m_worldUp = worldUP;
    m_forward = glm::normalize(position-target);
    m_right_direct =glm::normalize(glm::cross(worldUP,m_forward));
    m_up_direct = glm::normalize(glm::cross(m_forward,m_right_direct));

    m_lookAt_mat4 = glm::lookAt(m_position,target,worldUP);
}

glm::mat4 Camera::getViewMat()
{
    return m_lookAt_mat4;
}
