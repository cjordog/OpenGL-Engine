#include <iostream>
#include <unistd.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {
    
    // initialize GLFW
    glfwInit();
    // set GLFW to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // set profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // initialize GLFW window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // set the main thread's context to be the window's context
    glfwMakeContextCurrent(window);
    
    // initialize GLAD to grab OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // set viewport size to be window size
    int viewportWidth, viewPortHeight;
    //need to grab framebuffer size since retina displays dont use pixels as coords
    glfwGetFramebufferSize(window, &viewportWidth, &viewPortHeight);
    glViewport(0, 0, viewportWidth, viewPortHeight);
    
    // register callback function for window resizes
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    Shader shader("/Users/cjordog/Desktop/OpenGL_stuffs/OpenGL_Project/OpenGL_Project/shader.vs",
                  "/Users/cjordog/Desktop/OpenGL_stuffs/OpenGL_Project/OpenGL_Project/shader.fs");
    

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.25f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        
        0.0f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
        0.25f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    // create a VAO to store our vertex attributes
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // initialize VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // bind VBO to be our GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // load vertices into our vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // tell our vertex shader how to interpret our vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // enable our vertex attribute
    glEnableVertexAttribArray(0);
    // tell our vertex shader how to interpret our vertex buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // enable our vertex attribute
    glEnableVertexAttribArray(1);
 
    // create an EBO to store indices
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    // bind EBO to be our GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // load indices into our EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        
        // clear the screen
        glClearColor(0.2f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
