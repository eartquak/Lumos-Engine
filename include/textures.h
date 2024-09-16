#pragma once



#include "gl_stuff.h"
#include "shader.h"
#include "stb/stb_image.h"
#include <spdlog/spdlog.h>
#include "entt/entt.hpp"





class Texture {
    GLuint u_textures;
    Shader* shader;
  public:
    GLuint texIndex;
    GLuint ref;
    int width, height, numColCh;
    Texture(const char* path, GLenum format, GLenum pixelType, GLuint slot, Renderer& renderer);
    ~Texture();
    void texParameter(GLenum pname, GLint param);
    void load(GLuint slot);
    void unload();
    static std::vector<int> texUnits;
};







    



    

