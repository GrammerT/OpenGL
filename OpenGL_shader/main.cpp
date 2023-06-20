#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;




GLfloat vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};


uint32_t indices[]={
    0,1,2,
    2,3,0
};



void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}



int main()
{

//    int width,height,nrChannels;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char*data = stbi_load("D:\\workspace\\QTPro\\OpenGL_shader\\texture\\jpg.jpg",&width,&height,&nrChannels,0);
//    for(int i=0;i<100;++i)
//    {
//        std::cout<<(int)data[i]<<std::endl;
//    }
//    stbi_image_free(data);


    glm::vec4 vec(1.0f,0,0,1.0f);
    glm::mat4 trans=glm::mat4(1.0f);
    trans = glm::translate(trans,glm::vec3(1.0,1.0,-10.0));
    vec = trans*vec;
    std::cout<<" "<<vec.x<<" "<<vec.y<<" "<<vec.z;



    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow *window = glfwCreateWindow(800,600,"my opengl game",NULL,NULL);

    if(!window)
    {
        glfwTerminate();

        return -1;
    }


    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if(glewInit()!=GLEW_OK)
    {

        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,600);
//    glEnable(GL_BLEND);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    Shader *shader =new Shader("D:/workspace/MyPractice/OpenGL_shader/vertext.vert",
                               "D:/workspace/MyPractice/OpenGL_shader/fragment.frag");


    uint32_t VAO;

    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    uint32_t VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    uint32_t EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);



    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texBuffer;
    glGenTextures(1,&texBuffer);
    glBindTexture(GL_TEXTURE_2D,texBuffer);
    int width,height,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char*data = stbi_load("D:/workspace/MyPractice/OpenGL_shader/texture/jpg.jpg",&width,&height,&nrChannels,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"load error."<<std::endl;
    }
    stbi_image_free(data);


    while (!glfwWindowShouldClose(window)) {
        glm::mat4 transMat;
        transMat = glm::translate(transMat,glm::vec3(-0.3,0,0));
        transMat = glm::rotate(transMat,(float)glfwGetTime(),glm::vec3(0,0,1));//! 绕X轴
        transMat = glm::scale(transMat,glm::vec3(1,1.0f,0));
        processInput(window);

        glClearColor(0.2,0.5,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texBuffer);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

        shader->use();
        auto location = glGetUniformLocation(shader->m_shader_id,"transMat");
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(transMat));


        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
