#include "hull.hpp"

#include <algorithm>
#include <cmath>

Hull::Hull(const std::vector<Point>& points): points(points) {
    sort_points();
}

double Hull::get_square(const Point& point1, const Point& point2, const Point& point3) {
    return (point2.first - point1.first) * (point3.second - point1.second)
            - (point2.second - point1.second) * (point3.first - point1.first);
}

double Hull::get_vector_length(const Point& point, const Point& next_point) {
    return std::sqrt(std::pow(point.first - next_point.first, 2) + std::pow(point.second - next_point.second, 2));
}

void Hull::sort_points() {
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].first < points[0].first || (points[i].first == points[0].first && points[i].second < points[0].second)) {
            std::swap(points[i], points[0]);
        }
    }
    Point start_point = points[0];
    auto angle_cmp = [&] (const Point& point1, const Point& point2) {
        double square = get_square(start_point, point1, point2);
        return (std::abs(square) < EPS &&
                get_vector_length(start_point, point1) > get_vector_length(start_point, point2)) || square < 0;
    };
    std::sort(++points.begin(), points.end(), angle_cmp);
}

std::stack<Point> Hull::get_convex_hull() {
    std::stack<Point> stack;
    if (points.size() < 3) {
        return stack;
    }
    stack.push(points[0]);
    stack.push(points[1]);
    points.push_back(points[0]);
    for (size_t i = 2; i < points.size(); ++i) {
        Point top = stack.top(); stack.pop();
        Point top_top = stack.top(); stack.push(top);
        while (stack.size() > 2 && get_square(top_top, top, points[i]) >= 0) {
            stack.pop();
            top = stack.top(); stack.pop();
            top_top = stack.top(); stack.push(top);
        }
        stack.push(points[i]);
    }
    return stack;
}

double Hull::get_perimeter() {
    auto stack = get_convex_hull();
    if (stack.empty()) {
        return 0;
    }
    Point start = stack.top();;
    double sum = 0;
    while (stack.size() != 1) {
        auto point = stack.top(); stack.pop();
        auto next_point = stack.top();
        sum += get_vector_length(point, next_point);
    }
    auto point = start;
    auto next_point = stack.top();
    sum += get_vector_length(point, next_point);
    return sum;
}
