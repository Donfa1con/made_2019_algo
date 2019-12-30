#pragma once

#include <vector>
#include <stack>

const double EPS = 1e-6;
using Point = std::pair<double, double>;

class Hull {
  public:
    Hull(const std::vector<Point>& points);
    Hull(const Hull&) = delete;
    Hull(Hull&&) = delete;
    Hull& operator=(const Hull&) = delete;
    Hull& operator=(Hull&&) = delete;
    ~Hull() = default;
    
    double get_perimeter();
  private:
    void sort_points();
    std::stack<Point> get_convex_hull();
    
    static double get_square(const Point& point1, const Point& point2, const Point& point3);
    static double get_vector_length(const Point& point, const Point& next_point);

    std::vector<Point> points;
};
