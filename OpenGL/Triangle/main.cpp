/*
*	This code is part of The Cherno's OpenGL series on YouTube: https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
*	It is an excelant source of information fro anyone looking to get into OpenGL.
*/ 

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

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return -1;
    }
    
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}


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
    
    
    /*
    *   Start of the cool stuff
    */
    
    // Load GLAD
    gladLoadGL((GLADloadfunc) glfwGetProcAddress);
    
    // Set viewport
    glViewport(0, 0, WIDTH, HEIGHT);


    std::string vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
        
    std::string fragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(0.0, 1.0, 0.0, 1.0);"
        "}\n";
        
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

	/* Define vertices */
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3,
		0.5f, -0.5f * float(sqrt(3)) / 3,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,
	};

	/* Create VAO and VBO and configure them */
	GLuint VBO, VAO;
    
    /*
        void glGenVertexArrays(GLsizei n, GLuint *arrays);
        glGenVertexArrays returns n vertex array object names in arrays.
    */
	glGenVertexArrays(1, &VAO);
	
	/*
	    void glGenBuffers(GLsizei n, GLuint *buffers);
	    glGenBuffers returns n buffer names ib buffers
	*/
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	/* 
	    glVertexAttribPointer(
	        starting_index,
	        num_of_components_per_vertex_attrib,
	        type,
	        normalized,
	        stride,
	        pointer
	    )
	*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


    while(!glfwWindowShouldClose(window))
    {
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Resets the color
        glClear(GL_COLOR_BUFFER_BIT); // Clears color buffer
        glBindVertexArray(VAO); // Bind the VAO so it can be used
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float)); // Draws triangle with the VAO

        glfwSwapBuffers(window); // Swap the buffers
        glfwPollEvents(); // Get events
    }

	// Deletes the VAO, VBO, and shader program.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

