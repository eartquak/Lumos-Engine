#include "textures.h"

std::vector<int> Texture::texUnits = {};
// printf("Compiling...\n");
Shader* Texture::shader = nullptr;
// printf("Compiled...\n");

Texture::Texture(const char* path, GLenum format, GLenum pixelType,
                 GLuint slot) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* bytes = stbi_load(path, &width, &height, &numColCh, 0);

    if (bytes == NULL) {
        spdlog::error("Unable to open texture {}", path);
        exit(EXIT_FAILURE);
    }

    // Texture assumed to be GL_TEXTURE_2D
    glCreateTextures(GL_TEXTURE_2D, 1, &ref);

    // Image Internally stored as GL_RGBA8
    glTextureStorage2D(ref, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(ref, 0, 0, 0, width, height, format, pixelType, bytes);
    stbi_image_free(bytes);

    glGenerateTextureMipmap(ref);

    texParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    texParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    texParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

    load(slot);

    /*struct vertTex vertices[4];

    vertices[0].position = {rect.pos.x, rect.pos.y, 0.0f};
    vertices[1].position = {rect.pos.x + rect.dim.x, rect.pos.y, 0.0f};
    vertices[2].position = {rect.pos.x + rect.dim.x, rect.pos.y + rect.dim.y,
    0.0f}; vertices[3].position = {rect.pos.x, rect.pos.y + rect.dim.y, 0.0f};

    vertices[0].texCoord = {0.0f, 0.0f};
    vertices[1].texCoord = {1.0f, 0.0f};
    vertices[2].texCoord = {1.0f, 1.0f};
    vertices[3].texCoord = {0.0f, 1.0f};

    for(int i = 0; i < 4; i++) {
        vertices[i].colour = {0.0f, 0.0f, 1.0f};
    }

    for(int i = 0; i < 4; i++) {
        vertices[i].texIndex = static_cast<float>(texIndex);
    }

    for(int i = 0; i < 4; i++) {
        vertices[i].scale = 0.5f;
    }*/



    u_textures = glGetUniformLocation(shader->ref, "u_textures");
}

Texture::~Texture() { glDeleteTextures(1, &ref); }

void Texture::texParameter(GLenum pname, GLint param) {
    glTextureParameteri(ref, pname, param);
}

void Texture::load(GLuint slot) {
    glBindTextureUnit(slot, ref);
    texUnits.push_back(slot);
    this->texIndex = texUnits.size() - 1;
    glUniform1iv(u_textures, Texture::texUnits.size(),
                 Texture::texUnits.data());
}


void Texture::initShader() {
    shader = new Shader("./assets/shaders/vert.glsl",
                        "./assets/shaders/frag.glsl");
}

entt::entity sprite2D(App& app, glm::vec2 pos, glm::vec2 dim, float angle, glm::vec3 colour_in, Texture& texture) {
    
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
        vertQuad.vertices[i].colour = {0.0f, 0.0f, 1.0f};
    }

    for(int i = 0; i < 4; i++) {
        vertQuad.vertices[i].texIndex = static_cast<float>(texture.texIndex);
    }

    printf("banana\n");
    renderer& renderer_in = *(app.m_renderer);
    entt::registry& reg = app.reg;
    entt::entity s2Dentt = reg.create();
    reg.emplace<vertTexQuad>(s2Dentt, vertQuad);
    reg.emplace<isDrawn>(s2Dentt, true);
    reg.emplace<render>(s2Dentt, renderer_in, renderer_in.getFree());
    reg.emplace<colour>(s2Dentt, texture.texIndex, colour_in);
    render r = reg.get<render>(s2Dentt);
    renderer_in.updateData(r.slot, vertQuad);

    return s2Dentt;
}


void updateRectS2D(glm::vec2 pos, glm::vec2 dim, float angle, vertTexQuad& vertQuad_in) {
      
    struct vertTexQuad vertQuad;
    vertQuad.vertices[0].position = {pos.x, pos.y, 0.0f};
    vertQuad.vertices[1].position = {pos.x + dim.x, pos.y, 0.0f};
    vertQuad.vertices[2].position = {pos.x + dim.x, pos.y + dim.y,0.0f};
    vertQuad.vertices[3].position = {pos.x, pos.y + dim.y, 0.0f};
    vertQuad.vertices[0].texCoord = {0.0f, 0.0f};
    vertQuad.vertices[1].texCoord = {1.0f, 0.0f};
    vertQuad.vertices[2].texCoord = {1.0f, 1.0f};
    vertQuad.vertices[3].texCoord = {0.0f, 1.0f};

    vertQuad_in = vertQuad;
    
}



