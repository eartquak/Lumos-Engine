#include "../Lumos/lumos.cpp"

int main() {
    App app = App(800, 600, "Testing Window");
    // Quad* ps = new Quad({
    //                         -0.5f, -0.5f,  // Bottom-left vertex
    //                         0.5f, -0.5f,   // Bottom-right vertex
    //                         0.5f, 0.5f,    // Top-right vertex
    //                         -0.5f, 0.5f    // Top-left vertex
    //                     },
    //                     {1.0f, 0.0f, 0.0f});
    Quad* ps = new Quad(Vec2{-0.5f, -0.5f}, 1.0f, 1.0f, Color{1.0f, 0.0f, 0.0f});
    app.add_system(SystemType::Update, [&ps]() {
           ps->draw();
       })
        .run();
}

/*
{
                            -0.5f, -0.5f,  // Bottom-left vertex
                            0.5f, -0.5f,   // Bottom-right vertex
                            0.5f, 0.5f,    // Top-right vertex
                            -0.5f, 0.5f    // Top-left vertex
                        },
                        {1.0f, 0.0f, 0.0f});
       }*/