#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Camera.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;




//GLfloat vertices[] = {
////     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};



GLfloat  vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


uint32_t indices[]={
    0,1,2,
    2,3,0
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};


GLfloat radius = 19.0f;
GLfloat camX = sin(glfwGetTime()) * radius;
GLfloat camZ = cos(glfwGetTime()) * radius;
//        Camera camera(glm::vec3(0,0,3),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));

Camera camera(glm::vec3(0,0,3),glm::radians(-5.0f),glm::radians(180.0f),glm::vec3(0.0f,1.0f,0.0f));



void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }

    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
    {
        camera.m_speed_z=1.0;
    }
    else if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
    {
        camera.m_speed_z=-1.0;
    }
    else
    {
        camera.m_speed_z = 0;
    }

}

bool first_mouse = true;
double m_last_xpos,m_last_ypos;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(first_mouse)
    {
        m_last_ypos = ypos;
        m_last_xpos = xpos;
        first_mouse = false;
    }
    double deltX,deltY;
    deltX = xpos- m_last_xpos;
    deltY = m_last_ypos-ypos;

    m_last_xpos = xpos;
    m_last_ypos = ypos;

    camera.processMouseEvent(deltX,deltY);
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


//    glm::vec4 vec(1.0f,0,0,1.0f);
//    glm::mat4 trans=glm::mat4(1.0f);
//    trans = glm::translate(trans,glm::vec3(1.0,1.0,-10.0));
//    vec = trans*vec;
//    std::cout<<" "<<vec.x<<" "<<vec.y<<" "<<vec.z;

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

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window,mouse_callback);

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
    glEnable(GL_DEPTH_TEST);
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



    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
//    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


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




    glm::mat4 projMat;
    projMat = glm::perspectiveFov<double>(45.0f,800.0,600.0,0.1f,100.f);

    while (!glfwWindowShouldClose(window)) {
//        glm::mat4 transMat;
//        transMat = glm::translate(transMat,glm::vec3(-0.3,0,0));
//        transMat = glm::rotate(transMat,(float)glfwGetTime(),glm::vec3(0,0,1));//! 绕X轴
//        transMat = glm::scale(transMat,glm::vec3(1,1.0f,0));


        processInput(window);
        glClearColor(0.2,0.5,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texBuffer);


        shader->use();

        GLint modelLoc = glGetUniformLocation(shader->m_shader_id, "modelMat");

        GLint viewLoc = glGetUniformLocation(shader->m_shader_id, "viewMat");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMat()));
        GLint projLoc = glGetUniformLocation(shader->m_shader_id, "projMat");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));


        for(int i=0;i<10;++i)
        {
            glm::mat4 modelMat;
            modelMat = glm::translate(modelMat,cubePositions[i]);
            modelMat = glm::rotate(modelMat,(float)glfwGetTime(),glm::vec3(1.0,0.0,1.0));
            modelMat = glm::scale(modelMat,glm::vec3(1.01,1.01,1.01));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.updateCameraPos();
    }

    glfwTerminate();
    return 0;
}
