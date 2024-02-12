#pragma once



#include "gl_stuff.h"
#include "shader.h"
#include "stb/stb_image.h"
#include <stdio.h>
#include <spdlog/spdlog.h>
#include "entt/entt.hpp"
#include "lumos.h"


class Texture {
    static Shader* shader;
    GLuint u_textures;
  public:
    GLuint texIndex;
    GLuint ref;
    int width, height, numColCh;
    Texture(const char* path, GLenum format, GLenum pixelType, GLuint slot);
    ~Texture();
    void texParameter(GLenum pname, GLint param);
    void load(GLuint slot);
    void unload();
    static std::vector<int> texUnits;
    static void initShader();
};

entt::entity sprite2D(App& app, glm::vec2 pos, glm::vec2 dim, float angle, glm::vec3 colour_in, Texture& texture);


    

