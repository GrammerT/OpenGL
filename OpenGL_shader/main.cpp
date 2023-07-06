#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Camera.h"
#include "LightDirection.h"
#include "LightPoint.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;

//! model_data
#pragma region Model_Data
GLfloat  vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

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
#pragma endregion
//! model_data

GLfloat radius = 19.0f;
GLfloat camX = sin(glfwGetTime()) * radius;
GLfloat camZ = cos(glfwGetTime()) * radius;
//        Camera camera(glm::vec3(0,0,3),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));

Camera camera(glm::vec3(0,0,3),glm::radians(-5.0f),glm::radians(180.0f),glm::vec3(0.0f,1.0f,0.0f));
LightPoint light(glm::vec3(10.0f,10.0f,-5.0f),glm::vec3(glm::radians(45.0f),glm::radians(45.0),glm::radians(0.0)),
                     glm::vec3(10.0f,0.0f,0.0f));

//! input process.

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

    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
    {
        camera.m_speed_x=-1.0;
    }
    else if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
    {
        camera.m_speed_x=1.0;
    }
    else
    {
        camera.m_speed_x = 0;
    }

    if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS)
    {
        camera.m_speed_y=1.0;
    }
    else if(glfwGetKey(window,GLFW_KEY_E)==GLFW_PRESS)
    {
        camera.m_speed_y=-1.0;
    }
    else
    {
        camera.m_speed_y = 0;
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


//! create texture
unsigned int createTexture(const char* texture_path,GLint internalFormat,GLenum format,int textureslot)
{
    unsigned int texBuffer;
    glGenTextures(1,&texBuffer);
    glActiveTexture(GL_TEXTURE0+textureslot);
    glBindTexture(GL_TEXTURE_2D,texBuffer);
    int width,height,nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char*data = stbi_load(texture_path,&width,&height,&nrChannels,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,internalFormat,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"load error."<<std::endl;
    }
    stbi_image_free(data);
    return texBuffer;
}
//! end create texture

int main()
{
    //! open window.
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
    glEnable(GL_DEPTH_TEST);
    //! end open window.


    //! create and init shader.
    Shader *shader =new Shader("D:/workspace/MyPractice/OpenGL_shader/vertext.vert",
                               "D:/workspace/MyPractice/OpenGL_shader/fragment.frag");
    //! end

    //! create Material
    Material *myMaterial =new Material(shader,
                      createTexture("D:/workspace/MyPractice/OpenGL_shader/texture/container2.png",GL_RGBA,GL_RGBA,0),
                      glm::vec3(1.0f,1.0f,1.0f),
                      createTexture("D:/workspace/MyPractice/OpenGL_shader/texture/container2_specular.png",GL_RGBA,GL_RGBA,1),
                      32.0f);


    //! init and load Model to VAO & VBO
    uint32_t VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    uint32_t VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    //! end load model.
//    auto texBuffer = createTexture("D:/workspace/MyPractice/OpenGL_shader/texture/jpg.jpg",GL_RGB,GL_RGB,0);


    //! create MVP;
    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projMat;

    projMat = glm::perspectiveFov<double>(45.0f,800.0,600.0,0.1f,100.f);

    //! rend loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
//        glClearColor(0.2,0.5,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        for(int i=0;i<10;++i)
        {
            //! set model matrix.
            modelMat = glm::translate(glm::mat4(1.0f),cubePositions[i]);
//            modelMat = glm::rotate(modelMat,(float)glfwGetTime(),glm::vec3(1.0,0.0,1.0));
//            modelMat = glm::scale(modelMat,glm::vec3(1.01,1.01,1.01));

            //! set view and projMat here if you want.


            //! set Material -> shader program.
            shader->use();
            //! set Material -> texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, myMaterial->m_diffuse);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, myMaterial->m_specular);

            //! set Material -> uniforms.
            GLint modelLoc = glGetUniformLocation(shader->m_shader_id, "modelMat");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            GLint viewLoc = glGetUniformLocation(shader->m_shader_id, "viewMat");
            viewMat = camera.getViewMat();
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
            GLint projLoc = glGetUniformLocation(shader->m_shader_id, "projMat");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
            //! about light.
            GLint objLoc = glGetUniformLocation(shader->m_shader_id, "objColor");
            glUniform3f(objLoc,0.2f,0.2f,0.2f);
            GLint ambientLoc = glGetUniformLocation(shader->m_shader_id, "ambientColor");
            glUniform3f(ambientLoc,1.0f,1.0f,1.0f);
            GLint lightColorLoc = glGetUniformLocation(shader->m_shader_id, "lightColor");
            glUniform3f(lightColorLoc,light.m_color.x,light.m_color.y,light.m_color.z);
            GLint lightPosLoc = glGetUniformLocation(shader->m_shader_id, "lightPos");
            glUniform3f(lightPosLoc,light.m_position.x,light.m_position.y,light.m_position.z);
            GLint lightDir = glGetUniformLocation(shader->m_shader_id, "lightDir");
            glUniform3f(lightDir,light.m_direction.x,light.m_direction.y,light.m_direction.z);

//            float constant;
//            float linear;
//            float quadratic;
            GLint lightCon = glGetUniformLocation(shader->m_shader_id, "lightP.constant");
            GLint lightConline = glGetUniformLocation(shader->m_shader_id, "lightP.linear");
            GLint lightqua = glGetUniformLocation(shader->m_shader_id, "lightP.quadratic");

            glUniform1f(lightCon,light.m_constant);
            glUniform1f(lightConline,light.m_linear);
            glUniform1f(lightqua,light.m_quadratic);


            GLint CameraPosLoc = glGetUniformLocation(shader->m_shader_id, "cameraPos");
            glUniform3f(CameraPosLoc,camera.m_position.x,camera.m_position.y,camera.m_position.z);
            //! set matrial
//            vec3 ambient;
//            vec3 diffuse;
//            vec3 speclar;
//            float shininess;
            shader->setUniform3f("material.ambient",myMaterial->m_ambient);
            shader->setUniform1i("material.diffuse",0);
            shader->setUniform1i("material.speclar",1);
            shader->setUniform1f("material.shininess",myMaterial->m_shininess);

            //! set Model.
            glBindVertexArray(VAO);
            //! draw call
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //! clean up. prepare for next render loop.
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.updateCameraPos();
    }
    //! exit.
    glfwTerminate();
    return 0;
}
