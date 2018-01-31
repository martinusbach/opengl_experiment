#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <GLFW/glfw3.h>


using namespace std;
using namespace gl;


int main()
{
    cout << "Hello World!" << endl;

    // try creating a windowed opengl context with glfw
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed

    glfwMakeContextCurrent(window);

    // try out opengl binding
    glbinding::Binding::initialize();

    GLuint vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    std::cout << "vertex buffer id: " << vertexBuffer << " (should be 1)" << std::endl;

    // main event loop
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Done!
    glfwTerminate();

    return 0;
}
