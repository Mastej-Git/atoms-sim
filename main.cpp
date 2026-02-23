#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Engine {

    GLFWwindow* window;
    int width = 800;
    int height = 600;

public:

    Engine() {

        if (!glfwInit()) {
            std::cout << "Failed to initialize glfw" << std::endl;
            exit(-1);
        }

        this->window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
        if (!window) {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }

        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        glViewport(0, 0, fb_width, fb_height);
    }

    ~Engine() {
        glfwTerminate();   
    }

    void run() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    GLFWwindow* get_window() {
        return this->window;
    }
};

int main() {

    Engine engine;
    // glfwSetKeyCallback(engine.window, key_callback)

    while(!glfwWindowShouldClose(engine.get_window())) {
        engine.run();
    }

    return 0;
}