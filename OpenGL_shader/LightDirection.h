#ifndef LIGHTDIRECTION_H
#define LIGHTDIRECTION_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/rotate_vector.hpp"

class LightDirection
{
public:
    LightDirection(glm::vec3 position,glm::vec3 angles,glm::vec3 color=glm::vec3(1.0f,1.0f,1.0f));


    glm::vec3 m_position;
    glm::vec3 m_angles;
    glm::vec3 m_color;
    glm::vec3 m_direction;


    void updateDirection()
    {
        m_direction= glm::vec3(0,0,1.0f);
        m_direction=glm::rotateZ(m_direction,m_angles.z);
        m_direction=glm::rotateX(m_direction,m_angles.x);
        m_direction=glm::rotateY(m_direction,m_angles.y);
        m_direction*=-1;
    }
};

#endif // LIGHTDIRECTION_H
