//
// Created by Piotr Białas on 02/11/2021.
//

#include "glm/gtx/string_cast.hpp"

#include "Material.h"
#include "ColorMaterial.h"

#include "3rdParty/stb/stb_image.h"

namespace xe {

    GLint  ColorMaterial::uniform_map_Kd_location_ = 0;
    GLuint ColorMaterial::color_uniform_buffer_ = 0;
    GLuint ColorMaterial::shader_ = 0;

    void ColorMaterial::bind() {
        glUseProgram(program());
        int use_map_Kd = 1;

        if (texture_ > 0) {
            OGL_CALL(glUniform1i(uniform_map_Kd_location_, texture_unit_));
            OGL_CALL(glActiveTexture(GL_TEXTURE0 + texture_unit_));
            OGL_CALL(glBindTexture(GL_TEXTURE_2D, texture_));
            use_map_Kd = 1;
        }

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, color_uniform_buffer_);
        glBindBuffer(GL_UNIFORM_BUFFER, color_uniform_buffer_);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &Kd_[0]);
        glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), sizeof(GLint), &use_map_Kd);
        glBindBuffer(GL_UNIFORM_BUFFER, 0u);
    }

    void ColorMaterial::unbind() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0u);
        glBindTexture(GL_TEXTURE_2D, 0u);
    }

    void ColorMaterial::init() {
        auto program = xe::utils::create_program(
                {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/color_vs.glsl"},
                 {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/color_fs.glsl"}});

        if (!program) {
            std::cerr << "Invalid program" << std::endl;
            exit(-1);
        }

        shader_ = program;

        glUseProgram(program);

        glGenBuffers(1, &color_uniform_buffer_);

        glBindBuffer(GL_UNIFORM_BUFFER, color_uniform_buffer_);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) + 4 * sizeof(float), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0u);

        uniform_map_Kd_location_ = glGetUniformLocation(shader_, "map_Kd");
    }

    GLuint create_texture(const std::string &name) {

        stbi_set_flip_vertically_on_load(true);
        GLint width, height, channels;
        auto img = stbi_load(name.c_str(), &width, &height, &channels, 0);

        if (!img) {
            return 0;
        }

        GLenum format;

        if (channels == 3)
            format = GL_RGB;
        else if (channels == 4) {
            format = GL_RGBA;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0u);

        return texture;
    }
}