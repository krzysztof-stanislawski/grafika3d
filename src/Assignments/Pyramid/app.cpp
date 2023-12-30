#include "app.h"

#include <chrono> 

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application/utils.h"

void SimpleShapeApplication::init() {

	auto [w, h] = frame_buffer_size();

	auto program = xe::utils::create_program(
		{ {GL_VERTEX_SHADER, std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
		 {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"} });

	if (!program) {
		std::cerr << "Invalid program" << std::endl;
		exit(-1);
	}

	// Vertex and index data
	std::vector<GLfloat> vertices = {
		//base, ZX plane, CCW from left top,blue
		-0.5f,0.0f,0.5f,	0.0f,0.0f,1.0f,		// 0
		-0.5f,0.0f,-0.5f,	0.0f,0.0f,1.0f,		// 1
		 0.5f,0.0f,-0.5f,	0.0f,0.0f,1.0f,		// 2
		 0.5f,0.0f,0.5f,	0.0f,0.0f,1.0f,		// 3

		 //first side, red
		 0.0f,1.0f,0.0f,	1.0f,0.0f,0.0f,		// 4
		-0.5f,0.0f,0.5f,	1.0f,0.0f,0.0f,		// 5 from 0
		-0.5f,0.0f,-0.5f,	1.0f,0.0f,0.0f,		// 6 from 1

		//second side, green
		 0.0f,1.0f,0.0f,	0.0f,1.0f,0.0f,		// 7
		-0.5f,0.0f,-0.5f,	0.0f,1.0f,0.0f,		// 8 from 1
		 0.5f,0.0f,-0.5f,	0.0f,1.0f,0.0f,		// 9 from 2

		 //third side, purple
		 0.0f,1.0f,0.0f,	0.5f,0.0f,1.0f,		// 10
		 0.5f,0.0f,-0.5f,	0.5f,0.0f,1.0f,		// 11 from 2
		 0.5f,0.0f,0.5f,	0.5f,0.0f,1.0f,		// 12 from 3

		 //fourth side, yellow
		 0.0f,1.0f,0.0f,	1.0f,1.0f,0.0f,		// 13
		 0.5f,0.0f,0.5f,	1.0f,1.0f,0.0f,		// 14 from 3
		 -0.5f,0.0f,0.5f,	1.0f,1.0f,0.0f,		// 15 from 0
	};

	indices = {
		// half base - CCW front face down
		0, 1, 2,
		// half base - CW front face up
		0, 3, 2,	

		// sides
		4, 6, 5,			// red
		7, 9, 8,			// green
		10, 12, 11,			// purple
		13, 15, 14			// yellow

		//replace 2nd and 3rd coord to change face dir
	};

	// Uniform buffer setup for 'Modifier'
	GLuint uniformBuffer;
	glGenBuffers(1, &uniformBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

	// Set uniform data for 'Modifier'
	float strength = 1.0f;
	float color[3] = { 1.0f, 1.0f, 1.0f };

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float), &color);

	// Uniform buffer setup for 'Transformations'
	GLuint transformationBuffer;
	glGenBuffers(1, &transformationBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, transformationBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 16 * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformationBuffer);

	// Set uniform data for 'Transformations'
	proj = glm::perspective(glm::radians(45.0f), GLfloat(w) / GLfloat(h), 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(1.0f, 0.75f, 1.0f), // eye pos
		glm::vec3(0.0f, 1.0f, 0.0f),// target pos
		glm::vec3(0.0f, 1.0f, 0.0f)// up direction, -1 upside down
	);
	auto model = glm::mat4(0.5f); // scale
	glm::mat4 PVM = proj * view * model;
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(PVM));


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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set OpenGL state
	glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

	glViewport(0, 0, w, h);

	// Use the shader program
	glUseProgram(program);

}


//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<GLfloat>(currentTime - startTime).count();

	// Modify the view matrix to make the camera go around the pyramid
	glm::mat4 view = glm::lookAt(
		glm::vec3(2.0f * sin(time), -0.5f, 2.0f * cos(time)),  // eye pos
		glm::vec3(0.0f, 0.6f, 0.0f),  // target pos
		glm::vec3(0.0f, 1.0f, 0.0f)   // up direction
	);

	auto model = glm::mat4(0.5f); // scale
	glm::mat4 PVM = proj * view * model;
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(PVM));

	glBindVertexArray(vao_);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "Error: OpenGL rendering failed with code " << error << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindVertexArray(0);
}
