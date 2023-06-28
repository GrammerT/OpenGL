#include "Material.h"

Material::Material(Shader *shader, unsigned int diffuse, glm::vec3 ambient, glm::vec3 specular, float shininess)
{
    m_shader = shader;
    m_diffuse = diffuse;
    m_ambient = ambient;
    m_specular = specular;
    m_shininess = shininess;
}

