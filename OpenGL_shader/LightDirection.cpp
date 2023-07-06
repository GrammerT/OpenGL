#include "LightDirection.h"

LightDirection::LightDirection(glm::vec3 position, glm::vec3 angles, glm::vec3 color)
{
    m_position = position;
    m_angles = angles;
    m_color = color;
    updateDirection();
}
