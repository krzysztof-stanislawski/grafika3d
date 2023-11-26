//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Application/utils.h"

void SimpleShapeApplication::init() {
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    // A vector containing the x,y,z vertex coordinates for the triangle + its colors as r,g,b, A!
    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

            -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    };

    std::vector<GLushort> indices = {0, 1, 2, 0, 3, 4, 0, 4, 1,};

    // Generating the buffer and loading the vertex data into it.
    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Generating the buffer and loading indices data into it.
    GLuint i_buffer_handle;
    glGenBuffers(1, &i_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Create a buffer handle for the uniform block
    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);

    // Allocate memory for 8 floats (strength and color in the uniform block)
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);

    // Bind the buffer to the interface block in the fragment shader
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

    // Define variables for strength and color
    float strength = 0.75f;
    float color[3] = {0.2f, 0.5f, 0.8f};

    // Load data into the buffer respecting std140 layout rules
    // Calculate offsets and sizes based on std140 rules
        // Rule 1: Base alignment of float is 4 bytes
        // Rule 3: Array treated as tightly packed scalars
    GLintptr strengthOffset = 0;  // Offset for strength (4 bytes)
    GLintptr colorOffset = 4 * sizeof(float);  // Offset for color (3 * 4 bytes)

    // Load data into the buffer using glBufferSubData
    glBufferSubData(GL_UNIFORM_BUFFER, strengthOffset, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, colorOffset, 3 * sizeof(float), color);

    // Create a new buffer handle for the transformation block
    GLuint transformationBuffer;
    glGenBuffers(1, &transformationBuffer);
    // Bind the buffer to the GL_UNIFORM_BUFFER target
    glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
    // Allocate memory for the buffer respecting std140 layout rules for the transformation block
    // Rule 2: Alignment of vec2 is 8 bytes (two floats)
    // Rule 4: Alignment of vec2 array elements is 16 bytes
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, nullptr, GL_STATIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformationBuffer);

    // Create variables to hold values to be loaded into the buffer
    float theta = 1.0f * glm::pi<float>() / 6.0f;
    auto cs = std::cos(theta);
    auto ss = std::sin(theta);
    glm::mat2 rot{ cs, ss, -ss, cs };
    glm::vec2 trans{ 0.0f, -0.25f };
    glm::vec2 scale{ 0.5f, 0.5f };

    glBufferSubData(GL_UNIFORM_BUFFER, 0*sizeof(float), 2*sizeof(float), &scale);
    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(float), 2*sizeof(float), &trans);
    glBufferSubData(GL_UNIFORM_BUFFER, 4*sizeof(float), 2*sizeof(float), &rot[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 8*sizeof(float), 2*sizeof(float), &rot[1]);

    // This setups a Vertex Array Object (VAO) that  encapsulates
    // the state of all vertex buffers needed for rendering
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer_handle);

    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    // and this specifies how the data is layout in the buffer.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    //COLORS
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of vao "recording"

    // Setting the background color of the rendering window,
    // I suggest not to use white or black for better debuging.
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    // This setups an OpenGL vieport of the size of the whole rendering window.
    auto [w, h] = frame_buffer_size();
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
    // Binding the VAO will setup all the required vertex buffers.
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, (void *) 0);
    glBindVertexArray(0);
}
