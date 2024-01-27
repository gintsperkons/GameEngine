// Libraries
#include "GLAD/glad.h"
#include <GLFW/glfw3.h>
// Inbuilt
#include <iostream>
#include <vector>
// SourceCode
#include "../../FileHandling/FileHandling.h"
#include "../RendererStructures.h"
#include "OpenGLRenderer.h"

OpenGLRenderer::~OpenGLRenderer()
{
}

int OpenGLRenderer::Init(GLFWwindow *window)
{
    try
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD!");
        }

        glViewport(0, 0, 800, 600);

        std::vector<Vertex> meshVertices = {
            {{0.4, -0.4, 0.0}, {1.0, 0.0, 0.0}},
            {{0.4, 0.4, 0.0}, {0.0, 1.0, 0.0}},
            {{-0.4, 0.4, 0.0}, {0.0, 0.0, 1.0}},

            {{-0.4, 0.4, 0.0}, {0.0, 0.0, 1.0}},
            {{-0.4, -0.4, 0.0}, {1.0, 1.0, 0.0}},
            {{0.4, -0.4, 0.0}, {1.0, 0.0, 0.0}},
        };
        firstMesh = GLMesh(&meshVertices);

    std::string vertexShaderSourceString =  FileHandling::ReadFile("Shaders/base.vert");
    std::string fragmentShaderSourceString = FileHandling::ReadFile("Shaders/base.frag");

    const char* vertexShaderSource = vertexShaderSourceString.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

    std::cout << vertexShaderSource << std::endl;
    std::cout << fragmentShaderSource << std::endl;
        // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

void OpenGLRenderer::Draw()
{
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(firstMesh.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(glfwGetCurrentContext());
}

void OpenGLRenderer::Update()
{
}

void OpenGLRenderer::Destroy()
{
}

void OpenGLRenderer::CleanUp()
{
}
