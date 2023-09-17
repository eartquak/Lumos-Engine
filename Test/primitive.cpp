#include "../Lumos/lumos.cpp"

int main() {
    App app = App(800, 600, "Testing Window");

    // Create a Box
    Quad* box = new Quad(Vec2{0, 0}, 400, 400, Color{1.0f, 0.0f, 0.0f}, PointType::Pixel);

    // Create a Point
    Point* point = new Point(Vec2{0.0f, 0.0f}, Color{0.0f, 1.0f, 0.0f});

    // Create a circle
    Circle* circle = new Circle(Vec2{0.5f, 0.0f}, Color{0.0f, 0.0f, 1.0f}, 10.0f);

    // Create Points (a vector of points)
    // std::vector<Vec2> points;
    // points.push_back(Vec2{-0.2f, -0.2f});
    // points.push_back(Vec2{0.2f, -0.2f});
    // points.push_back(Vec2{0.0f, 0.2f});
    // Points* pointsShape = new Points(points, Color{0.0f, 0.0f, 1.0f});

    app.add_system(SystemType::Update, [&box]() {
           box->draw();
       })
        .add_system(SystemType::Update, [&point]() {
            point->draw();
        })
        .add_system(SystemType::Update, [&circle]() {
            circle->draw();
        })
        .run();
}