export module hatching;
#include<numbers>
#include<vector>
#include <stdexcept>

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

std::pair<double, double> findBmin(const std::vector<Point_2>& points, const double k);

export std::vector<Line_2> hatching(const std::vector<Point_2>& contour, double angle, double h);
