#include <iostream>
#include <thread>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    glfwInit();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    glfwTerminate();

    return 0;
}
