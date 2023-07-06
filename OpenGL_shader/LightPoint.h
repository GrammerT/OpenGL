#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/rotate_vector.hpp"
class LightPoint
{
public:
    LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color);

    glm::vec3 m_position;
    glm::vec3 m_angles;
    glm::vec3 m_color;
    glm::vec3 m_direction;


};

#endif // LIGHTPOINT_H
