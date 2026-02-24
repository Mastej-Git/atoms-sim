#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>


const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

class Circle {
    unsigned int VAO, VBO;
    std::vector<float> vertices;

public:
    Circle(float cx, float cy, float radius, int segments = 36) {
        vertices.push_back(cx);
        vertices.push_back(cy);

        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            vertices.push_back(cx + radius * cos(angle));
            vertices.push_back(cy + radius * sin(angle));
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void draw() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
    }

    ~Circle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

class Engine {
    GLFWwindow* window;
    unsigned int shaderProgram;

public:
    Engine() {
        if (!glfwInit()) {
            std::cout << "Failed to initialize glfw" << std::endl;
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
        if (!window) {
            std::cout << "Failed to create window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }

        glViewport(0, 0, 600, 600);
        compileShaders();
    }

    void compileShaders() {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void useShader() {
        glUseProgram(shaderProgram);
    }

    void clear() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void swapBuffers() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool shouldClose() {
        return glfwWindowShouldClose(window);
    }

    ~Engine() {
        glDeleteProgram(shaderProgram);
        glfwTerminate();
    }
};

int main() {
    Engine engine;
    Circle circle(0.0f, 0.0f, 0.5f, 50);

    while (!engine.shouldClose()) {
        engine.clear();
        engine.useShader();
        circle.draw();
        engine.swapBuffers();
    }

    return 0;
}