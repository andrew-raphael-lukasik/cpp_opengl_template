#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <spdlog/spdlog.h>



void framebuffer_size_changed_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    spdlog::error("window size changed to: {} : {}", width, height);
}

// src: https://iquilezles.org/articles/palettes/
glm::vec3 palette( const float t, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d ) { return a + b*cos(6.283185f*(c*t+d)); }

bool renderingInit (GLFWwindow* window)
{
    // initialize glad
    if (!gladLoadGL()) {
        spdlog::error("Failed to initialize glad");
        glfwTerminate();
        return false;
    }
    
    glfwSwapInterval(1);// 1 = vsync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_changed_callback);

    return true;
}

bool renderingTick (GLFWwindow* window, double time)
{
    glm::vec3 bg(palette(time*.1f,glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(2.0,1.0,0.0),glm::vec3(0.5,0.20,0.25)));
    glClearColor(bg.r, bg.g , bg.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);

    return true;
}
