#include <iostream>
#include "YukselC2Interpolation.h"

std::ostream &operator<<(std::ostream &os, const glm::vec2 &x)
{
    os << x[0] << ',' << x[1];
    return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &x)
{
    os << x[0] << ',' << x[1] << ',' << x[2];
    return os;
}

void example_2d()
{
    std::vector<glm::vec2> points{{0, 0}, {1, 1}, {2, 0}, {3, 1}, {4, 0}, {5, 1}};
    YukselC2Interpolation<glm::vec2, QuadraticBezierInterpolation<glm::vec2>> bezier(points);
    for (int segment = 0; segment < points.size() - 1; ++segment)
    {
        for (float theta = 0; theta < std::numbers::pi_v<float> / 2; theta += 0.01f)
            std::cout << bezier(segment, theta) << '\n';
    }
}

void example_3d()
{
    std::vector<glm::vec3> points{{0, 0, 0}, {1, 1, 1}, {2, 0, 2}, {3, 1, 3}, {4, 0, 4}, {5, 1, 5}};
    YukselC2Interpolation<glm::vec3, QuadraticBezierInterpolation<glm::vec3>> bezier(points);
    for (int segment = 0; segment < points.size() - 1; ++segment)
    {
        for (float theta = 0; theta < std::numbers::pi_v<float> / 2; theta += 0.01f)
            std::cout << bezier(segment, theta) << '\n';
    }
}

int main(int argc, char **argv)
{
    example_2d();
    return 0;
}
