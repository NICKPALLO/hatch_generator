module;
#include <numbers>
#include <vector>
#include <stdexcept>

export module hatching;

export constexpr double pi = std::numbers::pi;

export struct Point_2
{
	double x;
	double y;
};

export struct Line_2
{
	Point_2 first_point;
	Point_2 second_point;
};

/**
 * @brief Находит максимальное и минимальное значения коэффициента b для уравнений прямых штриховки (y = kx + b).
 *
 * @param points Вектор точек, описывающих контур прямоугольника.
 * @param k Коэффициент k прямой y = kx + b, определяющий наклон прямой.
 *
 * @return Пара значений (b_min, b_max).
 */
std::pair<double, double> findBminBmax(const std::vector<Point_2>& points, const double k);

/**
 * @brief Рассчитывает линии штриховки внутри заданного контура.
 * 
 * @param contour Вектор точек описывающих контур прямоугольника.
 * @param angle Угол наклона штриховки в градусах
 * @param h Шаг штриховки (должен быть > 0)
 * 
 * @return Вектор линий штриховки
 */
export std::vector<Line_2> hatching(const std::vector<Point_2>& contour, int angle, double h);
