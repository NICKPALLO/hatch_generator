#ifndef HATCHING_H
#define HATCHING_H

/**
 * @file hatching.cxx
 * @brief Файл реализующий модуль, который содержит структуры
 * описывающие геометрические примитивы и
 * функции для расчета линий штриховки замкнутого контура
 * (прямоугольника).
 */

#include <numbers>
#include <vector>

inline constexpr double pi = std::numbers::pi; ///< Константа pi 3.14


struct Point_2 /// Структура точки на плоскости.
{
    double x;
    double y;
};


struct Line_2 /// Структура линии на плоскости, состоящая из двух точек.
{
    Point_2 first_point;
    Point_2 second_point;
};

/**
 * @brief Функция, которая находит максимальное и минимальное
 * значения коэффициента b для уравнений прямых штриховки (y = kx + b).
 *
 * @param points Вектор точек, описывающих контур прямоугольника.
 * @param k Коэффициент k прямой y = kx + b, определяющий наклон прямой.
 * @throw std::runtime_error Если вектор points пуст.
 *
 * @return Пара значений (b_min, b_max).
 */
std::pair<double, double> findBminBmax(const std::vector<Point_2>& points, const double k);

/**
 * @brief Функция, которая рассчитывает линии штриховки внутри заданного контура прямоугольника.
 *
 * @param contour Вектор точек описывающих контур прямоугольника.
 * @param angle Угол наклона штриховки в градусах
 * @param h Шаг штриховки (должен быть > 0)
 *
 * @throw std::runtime_error Если вектор contour содержит не 4 точки или если шаг h <= 0.
 *
 * @return Вектор линий штриховки
 */
std::vector<Line_2> hatching(const std::vector<Point_2>& contour, int angle, double h);



#endif // HATCHING_H
