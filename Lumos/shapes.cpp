#pragma once
// #include "freeglut-3.4.0/include/GL/glut.h"
#include <iostream>

#include "math.cpp"

class Shape {
   public:
    Vec2 position;
    Color color;

    void draw();
};

class PrimitiveShape : public Shape {
   public:
    int height, width;
};

// We are assuming the vector point are given in such a fashion such that
// first two point are lower left points and they rest are present in a clockwise manner
class Quad : public PrimitiveShape {
   public:
    Quad(const std::vector<float>& coordinates, const std::vector<float>& color) {
        float min_x = std::min(std::min(coordinates[0], coordinates[2]), std::min(coordinates[4], coordinates[6]));
        float min_y = std::min(std::min(coordinates[1], coordinates[3]), std::min(coordinates[5], coordinates[7]));
        float max_x = std::max(std::max(coordinates[0], coordinates[2]), std::max(coordinates[4], coordinates[6]));
        float max_y = std::max(std::max(coordinates[1], coordinates[3]), std::max(coordinates[5], coordinates[7]));

        this->width = max_x - min_x;
        this->height = max_y - min_y;

        this->position = Vec2{min_x, min_y};
        this->color = Color{color[0], color[1], color[2]};
    }

    Quad(Vec2 position, int height, int width, Color color = {1.0, 1.0, 1.0}) {
        this->position = position;
        this->height = height;
        this->width = width;
        this->color = color;
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        glColor3f(color.r, color.g, color.b);  // Set the color
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + width, position.y);
        glVertex2f(position.x + width, position.y + height);
        glVertex2f(position.x, position.y + height);
        glEnd();

        glFlush();
    }
};