#include <iostream>
#include <cmath>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <GLFW/glfw3.h>


using namespace std;
using namespace gl;


void prepareTriangle(GLuint& shaderProgram, GLuint& fragmentShader, GLuint& vertexShader, GLuint& vbo, GLuint& vao)
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = R"glsl(
        #version 150 core
        in vec3 position;
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
    )glsl";
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = R"glsl(
        #version 150 core
        uniform vec3 triangleColor;
        out vec4 outColor;
        void main()
        {
            outColor = vec4(triangleColor, 1.0);
        }
    )glsl";
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(static_cast<GLuint>(posAttrib));
    glVertexAttribPointer(static_cast<GLuint>(posAttrib), 3, static_cast<gl::GLenum>(GL_FLOAT), GL_FALSE, 0, 0);
}

void cleanupTriangle(GLuint shaderProgram, GLuint fragmentShader, GLuint vertexShader, GLuint vbo, GLuint vao)
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

int main()
{
    cout << "Hello World!" << endl;

    glfwInit();

    // Create a windowed OpenGL context with GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    glbinding::Binding::initialize();

    GLuint shaderProgram, fragmentShader, vertexShader, vbo, vao;
    prepareTriangle(shaderProgram, fragmentShader, vertexShader, vbo, vao);

    // main event loop
    auto t_start = std::chrono::high_resolution_clock::now();
    while(!glfwWindowShouldClose(window))
    {
        // Clear the screen to black
        gl::glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
        glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        // Draw a triangle from the 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Cleanup
    cleanupTriangle(shaderProgram, fragmentShader, vertexShader, vbo, vao);

    glfwTerminate();

    // Done!
    return 0;
}
