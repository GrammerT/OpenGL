#include "Camera.h"

Camera::Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldUP)
{
    m_position = position;
    m_worldUp = worldUP;
    m_forward = glm::normalize(target-position);
    m_right_direct =glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up_direct = glm::normalize(glm::cross(m_right_direct,m_forward));


}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUP)
{
    m_position = position;
    m_worldUp = worldUP;
    m_pitch = pitch;
    m_yaw = yaw;
    m_forward.x = glm::cos(m_pitch)*glm::sin(m_yaw);
    m_forward.y = glm::sin(m_pitch);
    m_forward.z = glm::cos(m_pitch)*glm::cos(m_yaw);
    m_forward = glm::normalize(m_forward);

    m_right_direct =glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up_direct = glm::normalize(glm::cross(m_right_direct,m_forward));

}

glm::mat4 Camera::getViewMat()
{
    m_lookAt_mat4 = glm::lookAt(m_position,m_position+m_forward,m_worldUp);
    return m_lookAt_mat4;
}

void Camera::processMouseEvent(float deltX, float deltY)
{
    m_pitch-=deltY*0.002;
    m_yaw+=deltX*0.002;
    updateCameraVectors();
}

void Camera::updateCameraPos()
{
    m_position+=(m_forward * m_speed_z * 0.005f+m_right_direct*m_speed_x*0.005f+m_up_direct*m_speed_y*0.005f);
}

void Camera::updateCameraVectors()
{
    m_forward.x = glm::cos(m_pitch)*glm::sin(m_yaw);
    m_forward.y = glm::sin(m_pitch);
    m_forward.z = glm::cos(m_pitch)*glm::cos(m_yaw);
    m_forward = glm::normalize(m_forward);

    m_right_direct =glm::normalize(glm::cross(m_forward,m_worldUp));
    m_up_direct = glm::normalize(glm::cross(m_forward,m_right_direct));
}
