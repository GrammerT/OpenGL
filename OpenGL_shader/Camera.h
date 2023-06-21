#ifndef CAMERA_H
#define CAMERA_H
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera
{
public:
    explicit Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldUP);
    explicit Camera(glm::vec3 position,float pitch,float yaw,glm::vec3 worldUP);

    glm::mat4 getViewMat();

    void processMouseEvent(float deltX,float deltY);

    void updateCameraPos();
    float m_speed_z = 0.0;
private:
    void updateCameraVectors();


private:
    glm::vec3 m_position;
    glm::vec3 m_worldUp;
    glm::vec3 m_forward;//! 指向 y
    glm::vec3 m_right_direct;//! 右轴 x
    glm::vec3 m_up_direct;//! 上轴 z

    float m_pitch;
    float m_yaw;

    glm::mat4 m_lookAt_mat4 ;
};

#endif // CAMERA_H