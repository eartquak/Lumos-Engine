#pragma once

#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "vector"
#include "glm/glm.hpp"
#include <stdio.h>

#define REND_MAX 1000
   

class VBO {
  public:
    GLuint ref;
    VBO();
    ~VBO();
    void bind();
    void unbind();
    void addData(GLfloat *vertices, int size);   
    void updateData(GLfloat *vertices, int size, int offset);
};


class EBO {
  public:
    GLuint ref;
    EBO();
    ~EBO();
    void bind();
    void unbind();
    void addData(GLuint *indices, int size);
    void updateData(GLuint *indices, int size, int offset);
};

class VAO {
  public:
    GLuint ref;
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void draw(int count);
    void linkEnableAttrib(VBO* vbo,int ref, int numVals, GLenum type, int stride, void* offset); 
    void attachIndex(EBO* ebo);
};

// Restriction on number of quads rendered by renderer - 1000

struct vertTex {
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec2 texCoord;
    float texIndex;
};

struct vertTexQuad {
    vertTex vertices[4];
};

struct transform {
    glm::vec3 pos[4];
};

struct colour {
    GLint texIndex;
    glm::vec3 colour;
};

struct isDrawn {
    bool draw;
};

class apple {
    public:
    apple() {
        printf("apple\n");
    }
};


class renderer {
  public:
    VAO vao;
    //float vbo_data[4 * REND_MAX * sizeof(vertTex)];
    int vbo_pos = 0;
    VBO vbo;
    unsigned int ebo_data[6 * REND_MAX];
    EBO ebo;
    renderer();
    void updateData(int index, vertTexQuad data);
    void draw();
    int getFree();
};

struct render {
    renderer& m_renderer;
    int slot;
};
