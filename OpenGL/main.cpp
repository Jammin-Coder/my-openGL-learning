#include <iostream>
#include <cmath>

// GL libs
#define GLFW_INCLUDE_NONE
#include "libraries/include/glad/gl.h"
#include "gl.c"
#include <GLFW/glfw3.h>

int WIDTH = 800;
int HEIGHT = 800;
const char* NAME = "OpenGL Testing"; 

int main()
{
    // Initialize GLFW and return an error if failure occurs
    if(!glfwInit())
    {
        std::cout << "[-] ERROR: Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set context versions so that we have access to modern OpenGL functions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    // Creates new window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, NAME, NULL, NULL);

    // If window failes to be created, terminate GLFW.
    if(window == NULL)
    {
        std::cout << "[-] ERROR: Failed to initialize window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Bring window to the current context
    glfwMakeContextCurrent(window);

    // Load GLAD
    gladLoadGL((GLADloadfunc) glfwGetProcAddress);
    
    // Set viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

