#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Shader
{
public:
    Shader(const char *vertexPath,const char* fragmentPath);

    void use();

    void setUniform3f(const char* name,glm::vec3 param);
    void setUniform1f(const char*name ,float value);
    void setUniform1i(const char *name ,int slot);
    std::string vertexString;
    std::string fragString;
    const char *vertexSource;
    const char *fragSource;

    unsigned int m_shader_id;



private:
    void checkCompileErrors(unsigned int ID,std::string type);




};

#endif // SHADER_H
