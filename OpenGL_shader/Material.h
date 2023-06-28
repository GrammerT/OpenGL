#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class Material
{
public:
    Material(Shader *shader,unsigned int diffuse,glm::vec3 ambient,glm::vec3 specular,float shininess);


    unsigned int m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;
    float m_shininess;
    Shader *m_shader;
};

#endif // MATERIAL_H
