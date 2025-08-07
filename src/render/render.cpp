#include "render.h"
#include "../main.h"
#include "app.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "../libs/glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb/stb_perlin.h"

#include <spdlog/spdlog.h>


namespace render
{

    GLuint program;
    GLuint vertex_buffer, vertex_array;
    GLuint vertex_shader, fragment_shader;
    GLuint mvp_location, vpos_location, vcol_location;


    struct Vertex
    {
        glm::vec2 pos;
        glm::vec3 col;
    };

    const Vertex vertices[3] =
    {
        { { -0.6f, -0.4f }, { 1, 0, 0 } },
        { {  0.6f, -0.4f }, { 0, 1, 0 } },
        { {   0.f,  0.6f }, { 0, 0, 1 } }
    };

    void framebuffer_size_changed_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        spdlog::error("window size changed to: {} : {}", width, height);
    }

    // src: https://iquilezles.org/articles/palettes/
    glm::vec3 palette(const float t, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d) { return a + b*cos(6.283185f*(c*t+d)); }

    std::string load_text_file(const std::string& filePath)
    {
        std::ifstream shaderFile(filePath);
        if (!shaderFile.is_open()) {
            spdlog::error("Failed to open text file at path: {}", filePath);
            return "";
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }

    EFuncState init ()
    {
        // initialize glad
        if (!gladLoadGL()) {
            spdlog::error("Failed to initialize glad");
            glfwTerminate();
            return EFuncState::Failed;
        }
        
        glfwSwapInterval(1);// 1 = vsync
        glfwSetFramebufferSizeCallback(app::window, framebuffer_size_changed_callback);

        const GLubyte* glVersion = glGetString(GL_VERSION);
        if( glVersion ) {
            spdlog::info("OpenGL version detected: {}", *glVersion);
        }

        std::string vertex_shader_default_str = load_text_file("shaders/default-vertex-shader.glsl");
        const char* vertex_shader_default = vertex_shader_default_str.c_str();
        std::string fragment_shader_default_str = load_text_file("shaders/default-fragment-shader.glsl");
        const char* fragment_shader_default = fragment_shader_default_str.c_str();
        
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_default, NULL);
        glCompileShader(vertex_shader);
        {
            GLint success;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
                spdlog::error("vertex shader compilation failed:\n{}", infoLog);
            }
        }
    
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_default, NULL);
        glCompileShader(fragment_shader);
        {
            GLint success;
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
                spdlog::error("fragment shader compilation failed:\n{}", infoLog);
            }
        }
    
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
    
        mvp_location = glGetUniformLocation(program, "MVP");
        vpos_location = glGetAttribLocation(program, "vPos");
        vcol_location = glGetAttribLocation(program, "vCol");
    
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);
        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));

        return EFuncState::Succeded;
    }

    void tick ()
    {
        double time = glfwGetTime();

        int width, height;
        glfwGetFramebufferSize(app::window, &width, &height);
        const float ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glm::vec3 clearColor(palette(time*.1f,glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(2.0,1.0,0.0),glm::vec3(0.5,0.20,0.25)));
        glClearColor(clearColor.r, clearColor.g , clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4x4 m = glm::rotate(glm::mat4x4(1), (float)time, glm::vec3(0,0,1));// model rotates
        glm::mat4x4 v(1);
        v[3][0] = glm::sin(time);// view move sideways back and forth
        glm::mat4x4 p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glm::mat4x4 mvp = p * v * m;

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(app::window);
    }

    void close ()
    {
        
    }

}
