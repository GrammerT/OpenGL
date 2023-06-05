#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;



GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,   1.0,0,  0,
     0.5f, -0.5f, 0.0f,   0,  1.0,0,
     0.0f,  0.5f, 0.0f,   0,  0,  1.0,
     0.8f,0.8f,0.0f,      0.3,0.5,0.7
};

//GLfloat vertices[] = {
//    -0.5f, -0.5f, 0.0f,
//    0.5f, -0.5f, 0.0f,
//   0.0f,  0.5f, 0.0f,
//    0.5f, -0.5f, 0.0f,
//   0.0f,  0.5f, 0.0f,
//    0.8f,  0.8f, 0.0f,

//};

uint32_t indices[]={
    0,1,2,
    2,3,1
};



const char *vs = "#version 330 core \n"
"layout (location = 6) in vec3 pos; \n"
"layout (location = 7) in vec3 acolor; \n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
    "gl_Position = vec4(pos.x,pos.y,pos.z,1.0);\n"
    "vertexColor = vec4(acolor.x,acolor.y,acolor.z, 1.0f);\n"
"}\n";

const char *fs = "#version 330 core\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
    "color = vertexColor; \n"
"}";




//const char *vs =
//"#version 330 core           \n"
//"layout(location=0) in vec3 pos; \n"
//"void main(){                    \n"
//"        gl_Position = vec4(pos.x,pos.y,pos.z,1.0);}";



//const char *fs = "#version 330 core  \nout vec4 color;void main(){color=vec4(1.0f, 0.5f, 0.2f, 1.0f);}";


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



    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2,0.5,0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

        shader->use();

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
