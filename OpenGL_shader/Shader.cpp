#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"



Shader::Shader(const char *vertexPath,const char* fragmentPath)
{
    std::ifstream vertexFile;
    std::ifstream frageFile;

    std::stringstream vertexStream;
    std::stringstream fragStream;

    vertexFile.exceptions(std::ifstream::badbit);
    frageFile.exceptions(std::ifstream::badbit);

    vertexFile.open(vertexPath);
    frageFile.open(fragmentPath);

    std::cout<<"vertex file is open: "<<vertexFile.is_open()<<std::endl;
    if(!vertexFile.is_open())
    {

    }
    vertexStream<<vertexFile.rdbuf();
    vertexString = vertexStream.str();
    vertexSource = vertexString.c_str();
    std::cout<<"frag file is open: "<<frageFile.is_open()<<std::endl;
    if(!frageFile.is_open())
    {

    }
    fragStream<<frageFile.rdbuf();
    fragString = fragStream.str();
    fragSource = fragString.c_str();

    vertexFile.close();
    frageFile.close();

    GLuint vertex,fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertexSource,NULL);
    glCompileShader(vertex);

    checkCompileErrors(m_shader_id,"vertex");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragSource,NULL);
    glCompileShader(fragment);

    checkCompileErrors(m_shader_id,"fragment");

    m_shader_id = glCreateProgram();
    glAttachShader(m_shader_id,vertex);
    glAttachShader(m_shader_id,fragment);
    glLinkProgram(m_shader_id);

    checkCompileErrors(m_shader_id,"PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(m_shader_id);
}

void Shader::setUniform3f(const char *name, glm::vec3 param)
{
    glUniform3f(glGetUniformLocation(m_shader_id,name),param.x,param.y,param.z);
}

void Shader::setUniform1f(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(m_shader_id,name),value);
}

void Shader::setUniform1i(const char *name, int slot)
{
    glUniform1i(glGetUniformLocation(m_shader_id,name),slot);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
    int success;
    char infolog[512];
    if(type!="PROGRAM")
    {
        glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
        if(!success)
        {
            glGetShaderInfoLog(ID,512,NULL,infolog);
            std::cout<<type<<" shader compile error:"<<infolog<<std::endl;
        }
    }
    else
    {
        glGetProgramiv(ID,GL_LINK_STATUS,&success);
        if(!success)
        {
            glGetProgramInfoLog(ID,512,NULL,infolog);
            std::cout<<"program link error:"<<infolog<<std::endl;
        }
    }
}
