#include "app.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Application/utils.h"
#include "XeEngine/ColorMaterial.h"

void SimpleShapeApplication::init() {

    xe::ColorMaterial::init();

    set_camera(new Camera);
    set_controler(new CameraControler(camera()));

    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    // Vertex and index data
    std::vector<GLfloat> vertices = {
            //base, ZX plane, CCW from left top
            -0.5f, 0.0f, 0.5f,
            -0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, -0.5f,

            -0.5f, 0.0f, 0.5f,
            0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, 0.5f,

            //first side
            0.0f, 1.0f, 0.0f,
            -0.5f, 0.0f, 0.5f,
            -0.5f, 0.0f, -0.5f,

            //second side
            0.0f, 1.0f, 0.0f,
            -0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, -0.5f,

            //third side
            0.0f, 1.0f, 0.0f,
            0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, 0.5f,

            //fourth side
            0.0f, 1.0f, 0.0f,
            0.5f, 0.0f, 0.5f,
            -0.5f, 0.0f, 0.5f,
    };

    indices = {
            // half base - CCW front face down
            0, 1, 2,
            // half base - CCW front face down
            3, 4, 5,

            // sides
            6, 8, 7,
            9, 11, 10,
            12, 14, 13,
            15, 17, 16
    };

    // MeshesMaterials
    auto pyramid = new xe::Mesh;
    pyramid->allocate_vertex_buffer(vertices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
    pyramid->load_vertices(0, vertices.size() * sizeof(GLfloat), vertices.data());
    pyramid->vertex_attrib_pointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0);

    pyramid->allocate_index_buffer(indices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
    pyramid->load_indices(0, indices.size() * sizeof(GLfloat), indices.data());

    pyramid->add_submesh(0, 6, new xe::ColorMaterial({0.0f,0.0f,1.0f, 1.0f}));
    pyramid->add_submesh(6, 9, new xe::ColorMaterial({1.0f,0.0f,0.0f, 1.0f}));
    pyramid->add_submesh(9, 12, new xe::ColorMaterial({0.0f,1.0f,0.0f, 1.0f}));
    pyramid->add_submesh(12, 15, new xe::ColorMaterial({0.5f,0.0f,1.0f, 1.0f}));
    pyramid->add_submesh(15, 17, new xe::ColorMaterial({1.0f,1.0f,0.0f, 1.0f}));
    add_submesh(pyramid);

    // Uniform buffer setup for 'Modifier'
    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

    // Uniform buffer setup for 'Transformations'
    glGenBuffers(1, &transformationBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformationBuffer);

    int w, h;
    std::tie(w, h) = frame_buffer_size();

    camera_->perspective(glm::pi<float>() / 4.0, (float) w / h, 0.1f, 100.0f);
    camera_->look_at(
            glm::vec3(1.0f, 0.75f, 1.0f),    // eye pos
            glm::vec3(0.0f, .5f, 0.0f),        // target pos
            glm::vec3(0.0f, 1.0f, 0.0f)        // up direction, -1 upside down
    );

    // Vertex and index buffer setup
    GLuint v_buffer_handle, i_buffer_handle;
    glGenBuffers(1, &i_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // Generate Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);

    // Specify attribute data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set OpenGL state
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    // Use the shader program
    glUseProgram(program);

}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {

    glm::mat4 PVM = camera_->projection() * camera_->view();

    glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    for (auto m: meshes_) {
        m->draw();
    }

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void *) 0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error: OpenGL rendering failed with code " << error << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0, 0, w, h);
    auto aspect = (float) w / h;
    camera_->set_aspect(aspect);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom(yoffset / 30.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_->LMB_pressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_->LMB_released(x, y);
    }

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controler_) {
        controler_->mouse_moved(x, y);
    }
}