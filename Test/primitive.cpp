#include "../Lumos/lumos.cpp"

int main() {
    App app = App(800, 600, "Testing Window");

    // Create a Box
    Quad* box = new Quad(Vec2{0, 0}, 400, 400, Color{1.0f, 0.0f, 0.0f}, PointType::Pixel);

    // Create a Point
    Point* point = new Point(Vec2{0.0f, 0.0f}, Color{0.0f, 1.0f, 0.0f});

    // Create a circle
    Circle* circle = new Circle(Vec2{0.5f, 0.0f}, Color{0.0f, 0.0f, 1.0f}, 10.0f);

    std::vector<Vec2> points = {Vec2{0.0f, 0.0f}, Vec2{1.0f, 1.0f}};
    Line2D* line = new Line2D(points, Color{1.0, 1.0, 1.0}, PointType::Fraction);

    std::vector<Vec2> controlPoints;
    controlPoints.push_back(Vec2{100.0f, 100.0f});  // First control point
    controlPoints.push_back(Vec2{200.0f, 300.0f});  // Second control point
    controlPoints.push_back(Vec2{400.0f, 200.0f});  // Third control point
    controlPoints.push_back(Vec2{500.0f, 100.0f});  // Fourth control point

    BezierCurve* bezier_curve = new BezierCurve(controlPoints, Color{1.0f, 0.0f, 1.0f}, PointType::Pixel);

    // BezierCurve* curve =  new BezierCurve(points, )

    app.add_system(SystemType::Update, [&box]() {
           box->draw();
       })
        .add_system(SystemType::Update, [&point]() {
            point->draw();
        })
        .add_system(SystemType::Update, [&circle]() {
            circle->draw();
        })
        .add_system(SystemType::Update, [&line]() {
            line->draw();
        })
        .add_system(SystemType::Update, [&bezier_curve]() {
            bezier_curve->draw();
        })
        .run();
}