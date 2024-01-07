#pragma once

#include <vector>
#include "Application/application.h"
#include "Application/utils.h"
#include <glm/glm.hpp>

#include "glad/gl.h"
#include "camera.h"
#include "camera_controler.h"

#include "XeEngine/Mesh.h"
#include "XeEngine/Material.h"

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title,
                                                                                               debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    CameraControler *controler_;

    void set_controler(CameraControler *controler) { controler_ = controler; }

    void mouse_button_callback(int button, int action, int mods) override;

    void cursor_position_callback(double x, double y) override;

    Camera *camera_;

    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() { return camera_; }

    ~SimpleShapeApplication() {
        if (camera_) {
            delete camera_;
        }
    }

private:
    GLuint vao_;

    std::vector<GLushort> indices;

    GLuint transformationBuffer;

    void scroll_callback(double xoffset, double yoffset);

    std::vector<xe::Mesh *> meshes_;

    void add_submesh(xe::Mesh *mesh) {
        meshes_.push_back(mesh);
    }
};