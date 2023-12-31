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
#include "camera.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    Camera* camera_;

    void set_camera(Camera* camera) { camera_ = camera; }
    Camera* camera() { return camera_; }
    ~SimpleShapeApplication() {
        if (camera_) {
            delete camera_;
        }
    }

private:
    GLuint vao_;
    std::vector<GLushort> indices;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

    GLuint transformationBuffer;

    void scroll_callback(double xoffset, double yoffset);
};