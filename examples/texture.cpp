#include <cmath>
#include <vector>

#include "lumos.h"
#include "textures.h"
#include "shader.h"

int main() {
    App app = App(800, 800, "Testing Window", false, true);
    printf("setting up rects\n");
    rect texRect;
    texRect.pos = {-0.5f, -0.5f};
    texRect.dim = { 1.0f,  1.0f};
    Texture::initShader();
    Texture *tex = new Texture("./assets/ass.png", GL_RGB, GL_UNSIGNED_BYTE, texRect, 0);

    app.add_system(SystemType::Update, [tex]() {
            tex->draw();
        });

    app.run();
}

    

