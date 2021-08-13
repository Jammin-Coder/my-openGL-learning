#include <iostream>
#include <cmath>

// GL libs
#define GLFW_INCLUDE_NONE
#include "../libraries/include/glad/gl.h"
#include "../gl.c"
#include <GLFW/glfw3.h>

int WIDTH = 800;
int HEIGHT = 800;
const char* NAME = "OpenGL Testing"; 


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	/*
	*   Create shaders
	*/


	// VERTEX SHADERS
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Set the shader source
	glCompileShader(vertexShader); // compile the shader

	// FRAGMENT SHADERS
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*
	*   Create shader programs
	*/
	GLuint shaderProgram = glCreateProgram(); // New shader program
	// Adds or "attaches" the specified shaders to the shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); // Links the program specified by program

	// Deletes the 2 shaders since they are now stored in the shaderProgram
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*
	* Define vertices
	*/
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	/* Create VAO and VBO and configure them */
	GLuint VBO, VAO;

	/*******************
	* TODO: Figure out what all this does!
	*******************/

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Resets the color
        glClear(GL_COLOR_BUFFER_BIT); // Clears color buffer
        glUseProgram(shaderProgram); // Tells OpenGl to use the shaderProgram
        glBindVertexArray(VAO); // Bind the VAO so it can be used
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draws triangle with the VAO

        glfwSwapBuffers(window); // Swap the buffers
        glfwPollEvents(); // Get events
    }

	// Deletes the VAO, VBO, and shader program.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




