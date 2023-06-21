#include "Camera.h"

Camera::Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldUP)
{
    m_position = position;
    m_worldUp = worldUP;
    m_forward = glm::normalize(target-position);
    m_right_direct =glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up_direct = glm::normalize(glm::cross(m_forward,m_right_direct));


}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUP)
{
    m_position = position;
    m_worldUp = worldUP;
    m_forward.x = glm::cos(pitch)*glm::sin(yaw);
    m_forward.y = glm::sin(pitch);
    m_forward.z = glm::cos(pitch)*glm::cos(yaw);
    m_forward = glm::normalize(m_forward);

    m_right_direct =glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up_direct = glm::normalize(glm::cross(m_forward,m_right_direct));

}

glm::mat4 Camera::getViewMat()
{
    m_lookAt_mat4 = glm::lookAt(m_position,m_position+m_forward,m_worldUp);
    return m_lookAt_mat4;
}
