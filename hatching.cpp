#include "hatching.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

template class std::vector<Point_2>;
template class std::vector<Line_2>;

std::pair<double, double> findBminBmax(const std::vector<Point_2>& points, const double k)
{
    if (points.empty())
    {
        throw std::runtime_error("there are no points");
    }

    std::vector<Point_2>::const_iterator nearPoint;
    std::vector<Point_2>::const_iterator farPoint;
    if (k < 0)
    {
        nearPoint = std::min_element(points.begin(), points.end(), [](const Point_2& p1, const Point_2& p2) {
            return (p1.x + p1.y) < (p2.x + p2.y);
        });
        farPoint = std::max_element(points.begin(), points.end(), [](const Point_2& p1, const Point_2& p2) {
            return (p1.x + p1.y) < (p2.x + p2.y);
        });
    }
    else
    {
        nearPoint = std::min_element(points.begin(), points.end(), [](const Point_2& p1, const Point_2& p2) {
            return (p1.y <= p2.y) && (p1.x >= p2.x);
        });
        farPoint = std::max_element(points.begin(), points.end(), [](const Point_2& p1, const Point_2& p2) {
            return (p1.y <= p2.y) && (p1.x >= p2.x);
        });
    }
    return { nearPoint->y - k * nearPoint->x, farPoint->y - k * farPoint->x };
}

std::vector<Line_2> hatching(const std::vector<Point_2>& contour, int angle, double h)
{
    if (contour.size() != 4)
    {
        throw std::runtime_error("contour is not a rectangle or it is empty");
    }
    if (h <= 0)
    {
        throw std::runtime_error("wrong step");
    }
    angle = angle % 360;

    double x_min = std::min_element(contour.begin(), contour.end(), [](const Point_2& p1, const Point_2& p2) {
                       return p1.x < p2.x;
                   })->x;

    double x_max = std::max_element(contour.begin(), contour.end(), [](const Point_2& p1, const Point_2& p2) {
                       return p1.x < p2.x;
                   })->x;

    double y_min = std::min_element(contour.begin(), contour.end(), [](const Point_2& p1, const Point_2& p2) {
                       return p1.y < p2.y;
                   })->y;

    double y_max = std::max_element(contour.begin(), contour.end(), [](const Point_2& p1, const Point_2& p2) {
                       return p1.y < p2.y;
                   })->y;


    std::vector<Line_2> hatch;

    if (angle != 90 && angle != 270 && angle != 0 && angle != 180)
    {
        double angle_rad = angle * pi / 180;
        double k = tan(angle_rad);
        double delta_b = abs(h / cos(angle_rad));

        auto b_pair = findBminBmax(contour, k);
        double b_min = b_pair.first;
        double b_max = b_pair.second;

        double b = b_min + delta_b;

        hatch.reserve(static_cast<int>((b_max - b)/delta_b));

        while (b < b_max)
        {
            double x1, x2, y1, y2;
            if (k > 0)
            {
                x1 = std::max(x_min, (y_min - b) / k);
                y1 = std::max(y_min, k * x_min + b);
                x2 = std::min(x_max, (y_max - b) / k);
                y2 = std::min(y_max, k * x_max + b);
            }
            else
            {
                x1 = std::max(x_min, (y_max - b) / k);
                y1 = std::min(y_max, k * x_min + b);
                x2 = std::min(x_max, (y_min - b) / k);
                y2 = std::max(y_min, k * x_max + b);
            }
            hatch.push_back({ {x1,y1},{x2,y2} });
            b += delta_b;
        }
    }
    else
    {
        if (angle == 90 || angle == 270)
        {
            double x = x_min+h;
            double y1 = y_min;
            double y2 = y_max;
            hatch.reserve(static_cast<int>((x_max - x) / h));
            while (x < x_max)
            {
                hatch.push_back({ {x,y1},{x,y2} });
                x += h;
            }
        }
        else
        {
            double x1 = x_min;
            double x2 = x_max;
            double y = y_min+h;
            hatch.reserve(static_cast<int>((y_max - y) / h));
            while (y < y_max)
            {
                hatch.push_back({ {x1,y},{x2,y} });
                y += h;
            }
        }
    }

    return hatch;
}



