#ifndef SHADER_H
#define SHADER_H
#include <string>

class Shader
{
public:
    Shader(const char *vertexPath,const char* fragmentPath);

    void use();


    std::string vertexString;
    std::string fragString;
    const char *vertexSource;
    const char *fragSource;

    unsigned int m_shader_id;



private:
    void checkCompileErrors(unsigned int ID,std::string type);




};

#endif // SHADER_H
