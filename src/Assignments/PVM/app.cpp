#include "app.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application/utils.h"

void SimpleShapeApplication::init() {
    // Compile shaders and create program
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER, std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    // Define vertex and index data
    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    };

    std::vector<GLushort> indices = {0, 1, 2, 0, 3, 4, 0, 4, 1,};

    // Generate buffers and load data
    GLuint v_buffer_handle, i_buffer_handle,uniformBuffer,transformationBuffer,u_pvm_buffer;

    glGenBuffers(1, &v_buffer_handle);
    glGenBuffers(1, &i_buffer_handle);
    glGenBuffers(1, &uniformBuffer);
    glGenBuffers(1, &transformationBuffer);
    glGenBuffers(1, &u_pvm_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float strength = 0.75f;
    GLfloat color[3] = {0.2f, 0.5f, 0.8f};
    GLintptr strengthOffset = 0;
    GLintptr colorOffset = 4 * sizeof(float);

    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, strengthOffset, sizeof(float), & strength);
    glBufferSubData(GL_UNIFORM_BUFFER, colorOffset, 3 * sizeof(float), color);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);


    glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 12 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformationBuffer);

    // Create PVM
    glm::mat4 viewMat = glm::lookAt(
            glm::vec3(-1.0f, -1.f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto[w, h] = frame_buffer_size();
    glm::mat4 perMat = glm::perspective(glm::radians(45.0f), GLfloat(w) / GLfloat(h), 0.1f, 100.0f);
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(115.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 PVM = perMat * viewMat * modelMat;

    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &PVM[0][0], GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer);

    GLintptr index = 0;
    glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &PVM[0]);
    index += 4 * sizeof(float);
    glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &PVM[1]);
    index += 4 * sizeof(float);
    glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &PVM[2]);
    index += 4 * sizeof(float);
    glBufferSubData(GL_UNIFORM_BUFFER, index, 4 * sizeof(float), &PVM[3]);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Generate Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);

    // Specify attribute data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set OpenGL state
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    auto [viewport_w, viewport_h] = frame_buffer_size();
    glViewport(0, 0, viewport_w, viewport_h);

    // Use the shader program
    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, (void *)0);
    glBindVertexArray(0);
}
