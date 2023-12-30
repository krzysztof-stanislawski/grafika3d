//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>
#include <chrono> 
#include "Application/application.h"
#include "Application/utils.h"
#include <glm/glm.hpp>

#include "glad/gl.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

private:
    GLuint vao_;
    std::vector<GLushort> indices;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 P_;
    glm::mat4 V_;

    GLuint transformationBuffer;
};