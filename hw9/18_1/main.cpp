/*
18. Выпуклая оболочка 2D.
Дано множество точек на плоскости (x, y).
Постройте выпуклую оболочку этого множества и вычислите ее периметр.
Формат ввода
Количество точек, далее на каждой строке координаты точек x, y.
Общее количество точек не превосходит 100000.
Координаты точек - числа с плавающей точкой в диапазоне [-1000, 1000].
Формат вывода
Выведите периметр выпуклой оболочки.
Пример
Ввод    Вывод
3       4.65028154
1. 1.
2. 1.
0. 0.
*/
#include "hull/hull.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        double x = 0, y = 0;
        std::cin >> x >> y;
        points[i] = std::make_pair(x, y);
    }
    Hull hull(points);
    std::cout << std::setprecision(12) << hull.get_perimeter();
    return 0;
}
