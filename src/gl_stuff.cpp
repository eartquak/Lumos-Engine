#include "gl_stuff.h"




VAO::VAO() {
    glGenVertexArrays(1, &ref);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ref);
}

void VAO::bind() {
    glBindVertexArray(ref);
}

void VAO::unbind() {
    glBindVertexArray(0);
} 

void VAO::draw(int count) {
    this->bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void *)0);
    this->unbind();
}

void VAO::linkEnableAttrib(VBO* vbo, int ref, int numVals, GLenum type, int stride, void* offset) {
    this->bind();
    vbo->bind();
    glVertexAttribPointer(ref, numVals, type, GL_FALSE, stride, offset); 
    glEnableVertexAttribArray(ref);
    vbo->unbind();
    this->unbind();
}

void VAO::attachIndex(EBO* ebo) {
    this->bind();
    ebo->bind();
    this->unbind();
    ebo->unbind();
}



VBO::VBO() {
    glGenBuffers(1, &ref);
}

VBO::~VBO() {
    glDeleteBuffers(1, &ref);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ref);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::addData(GLfloat *vertices, int size) {
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, vertices, GL_DYNAMIC_DRAW);
    this->unbind();
}

void VBO::updateData(GLfloat *vertices, int size, int offset) {
    this->bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
    this->unbind();
}



EBO::EBO() {
    glGenBuffers(1, &ref);
};

EBO::~EBO() {
    glDeleteBuffers(1, &ref);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ref);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::addData(GLuint *indices, int size) {
    this->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
    this->unbind();
}

void EBO::updateData(GLuint *indices, int size, int offset) {
    this->bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
    this->unbind();
}

OpenGL::OpenGL(Window& window) {

    // Initialize GLEW (or other OpenGL loader) after creating the context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        spdlog::error("GLEW error: {}", (const char*)glewGetErrorString(err));
        glfwTerminate();
        return;
    }

#ifdef DEBUG
    int context_flag = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &context_flag);

    if (context_flag & GL_CONTEXT_FLAG_DEBUG_BIT) {
        spdlog::info("Debug context created");
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }
    else {
        spdlog::error("Unable to create debug context");
    }
#endif
    spdlog::info("OpenGL Initialized");
}

Renderer::Renderer(Window& window) :
    window(window), 
    openGL(window) {

    //TODO: keep shaders within file
    shader = new Shader("./assets/shaders/vert.glsl", "./assets/shaders/frag.glsl");
    vao.attachIndex(&ebo);
    ebo.addData(nullptr, sizeof(indexData) * REND_MAX);
    vbo.addData(nullptr, REND_MAX * sizeof(vertTexQuad));
    vao.attachIndex(&ebo);
    
    vao.linkEnableAttrib(&vbo, 0, 3, GL_FLOAT, sizeof(struct vertTex),
                         (void*)offsetof(vertTex, position));
    vao.linkEnableAttrib(&vbo, 1, 3, GL_FLOAT, sizeof(struct vertTex),
                         (void*)offsetof(vertTex, colour));
    vao.linkEnableAttrib(&vbo, 2, 2, GL_FLOAT, sizeof(struct vertTex),
                         (void*)offsetof(vertTex, texCoord));
    vao.linkEnableAttrib(&vbo, 3, 1, GL_FLOAT, sizeof(struct vertTex),
                         (void*)offsetof(vertTex, texIndex));

    spdlog::info("Renderer Initialized");
    
}

void Renderer::updateData(int index, vertTexQuad* vData, indexData iData) {
    if (vData != nullptr) {
        vbo_data[index] = *vData;
    }
    //uint indexData[] = INDEX((uint)index);
    ebo_data[index] = iData;
}

void Renderer::draw() {
    vbo.updateData((float*)vbo_data, vbo_pos * sizeof(vertTexQuad), 0);
    ebo.updateData((uint*)ebo_data, vbo_pos * sizeof(indexData), 0);
    shader->Activate();
    vao.draw(vbo_pos * 6);
    vbo_pos = 0;
}


void Renderer::drawQuad(glm::vec2 pos, glm::vec2 dim, glm::vec3 col, GLint texIndex) {
    //float angle = rect.angle;
    //angle = angle + 1;
    struct vertTexQuad vertQuad;
    vertQuad.vertices[0].position = {pos.x, pos.y, 0.0f};
    vertQuad.vertices[1].position = {pos.x + dim.x, pos.y, 0.0f};
    vertQuad.vertices[2].position = {pos.x + dim.x, pos.y + dim.y,0.0f};
    vertQuad.vertices[3].position = {pos.x, pos.y + dim.y, 0.0f};
    vertQuad.vertices[0].texCoord = {0.0f, 0.0f};
    vertQuad.vertices[1].texCoord = {1.0f, 0.0f};
    vertQuad.vertices[2].texCoord = {1.0f, 1.0f};
    vertQuad.vertices[3].texCoord = {0.0f, 1.0f};

    for(int i = 0; i < 4; i++) {
        vertQuad.vertices[i].colour = col;
    }

    for(int i = 0; i < 4; i++) {
        vertQuad.vertices[i].texIndex = static_cast<float>(texIndex);
    }
    int index = vbo_pos++;
    updateData(index, &vertQuad, INDEX((uint)index));
    if (index == REND_MAX - 1) {
        draw();
    }
}


void Renderer::drawCanvasCol(Position pos, Canvas canv, ColInfo colInfo) {
    //float angle = rect.angle;
    //angle = angle + 1;
    
    vertTexQuad vertQuad;

    glm::vec4 corners[4];
    corners[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
    corners[1] = { 0.0f, canv.dimensions.y, 0.0f, 1.0f };
    corners[2] = { canv.dimensions.x, canv.dimensions.y, 0.0f, 1.0f };
    corners[3] = { canv.dimensions.x, 0.0f, 0.0f, 1.0f };

    glm::mat4 rot = glm::mat4(1.0f);
    rot = glm::rotate(rot, glm::radians(canv.angle), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 scl = glm::mat4(1.0f);
    scl = glm::scale(scl, glm::vec3(canv.scales.x, canv.scales.y, 0.0f));

    glm::mat4 transPos = glm::mat4(1.0f);
    transPos = glm::translate(transPos, glm::vec3(pos.x, pos.y, pos.z));

    glm::mat4 transOff = glm::mat4(1.0f);
    transOff = glm::translate(transOff, glm::vec3(canv.offset.x, canv.offset.y, 0.0f));


    for (int i = 0; i < 4; i++) {
        corners[i] = transOff * (transPos * (scl * (rot * corners[i])));
        vertQuad.vertices[i].position = corners[i];
    }

    vertQuad.vertices[0].texCoord = {0.0f, 0.0f};
    vertQuad.vertices[1].texCoord = {1.0f, 0.0f};
    vertQuad.vertices[2].texCoord = {1.0f, 1.0f};
    vertQuad.vertices[3].texCoord = {0.0f, 1.0f};

    for(int i = 0; i < 4; i++) {
        vertQuad.vertices[i].colour = { colInfo.colour[i].x, colInfo.colour[i].y, colInfo.colour[i].z } ;
    }

    for(int i = 0; i < 4; i++) {
        vertQuad.vertices[i].texIndex = static_cast<float>((GLint)-1);
    }
    int index = vbo_pos++;
    updateData(index, &vertQuad, INDEX((uint)index));
    if (index == REND_MAX - 1) {
        draw();
    }
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::markFrameTermination() {
    glFrameTerminatorGREMEDY();
}


void glDebugOutput(GLenum source, GLenum type, 
                    unsigned int id, GLenum severity, 
                    GLsizei length, const char *message, 
                    const void *userParam) {

    switch (type) {
        case GL_DEBUG_TYPE_ERROR: 
            spdlog::error("OpenGL Error Message ID {0}: {1}", id, message);
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            spdlog::debug("OpenGL Debug Message (Deprecated Behaviour) ID {0}:, {1}", id, message);
            break;
        default:
            spdlog::debug("OpenGL Debug Message ID {0}: {1}", id, message);

    }
}


