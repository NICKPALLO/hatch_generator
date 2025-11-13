#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <string>
#include <fstream>

constexpr double pi = std::numbers::pi;

struct Point_2
{
	double x;
	double y;
};

struct Line_2
{
	Point_2 first_point;
	Point_2 second_point;
};

//first - b_min, second - b_max
std::pair<double,double> findBmin(const std::vector<Point_2>& points, const double k)
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

int main()
{
	//исходные данные
	std::vector<std::vector<Point_2>> contoursPoints = {
		{ {0,0}, {100,0}, {100,100}, {0,100} }
	};
	double angle = 45;
	double h = 20;



	double angle_rad = angle * pi / 180;
	double k = tan(angle_rad);
	double delta_b = h / cos(angle_rad);

	std::string xml_text ="<svg xmlns = \"http://www.w3.org/2000/svg\"\n"
		"width = \"100%\" height = \"100%\"\n"
		"viewBox = \"0 0 400 200\"\n"
		"version = \"1.1\" >\n\n";



	for (int cur_cont = 0; cur_cont < contoursPoints.size(); ++cur_cont)
	{
		auto b_pair = findBmin(contoursPoints[cur_cont], k);
		double b_min = b_pair.first;
		double b_max = b_pair.second;

		double x_min = std::min_element(contoursPoints[cur_cont].begin(), contoursPoints[cur_cont].end(), [](const Point_2& p1, const Point_2& p2) {
			return p1.x < p2.x;
			})->x;

		double x_max = std::max_element(contoursPoints[cur_cont].begin(), contoursPoints[cur_cont].end(), [](const Point_2& p1, const Point_2& p2) {
			return p1.x < p2.x;
			})->x;

		double y_min = std::min_element(contoursPoints[cur_cont].begin(), contoursPoints[cur_cont].end(), [](const Point_2& p1, const Point_2& p2) {
			return p1.y < p2.y;
			})->y;

		double y_max = std::max_element(contoursPoints[cur_cont].begin(), contoursPoints[cur_cont].end(), [](const Point_2& p1, const Point_2& p2) {
			return p1.y < p2.y;
			})->y;


		double b = b_min + delta_b;
		std::vector<Line_2> hatch;

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
		for (const auto& line : hatch)
		{
			std::string line_text = "<line x1 = \"" + std::to_string(line.first_point.x) +
				"\" y1 = \"" + std::to_string(line.first_point.y) + "\" x2 = \"" +
				std::to_string(line.second_point.x) + "\" y2 = \"" + std::to_string(line.second_point.y) +
				"\" \nstroke = \"#000000\" stroke-width = \"1\" stroke-linecap = \"round\" /> \n";
			xml_text += line_text;
		}
		for (int point = 0; point < contoursPoints[cur_cont].size();++point)
		{
			std::string line_text = "<line x1 = \"" + std::to_string(contoursPoints[cur_cont][point].x) +
				"\" y1 = \"" + std::to_string(contoursPoints[cur_cont][point].y) + "\" x2 = \"";

			if (point == contoursPoints[cur_cont].size()-1)
			{
				line_text+= std::to_string(contoursPoints[cur_cont][0].x) + "\" y2 = \"" + std::to_string(contoursPoints[cur_cont][0].y) +
					"\" \nstroke = \"#000000\" stroke-width = \"1\" /> \n";
			}
			else
			{
				line_text += std::to_string(contoursPoints[cur_cont][point+1].x) + "\" y2 = \"" + 
					std::to_string(contoursPoints[cur_cont][point+1].y) +
					"\" \nstroke = \"#000000\" stroke-width = \"1\" /> \n";
			}
			xml_text += line_text;
		}
		xml_text += "</svg>";
	}
	
	std::ofstream file("../../../test.xml");
	if (file.is_open())
	{
		std::cout << "all works";
		file << xml_text;
	}
	else
	{
		std::cout << "no";
	}
	file.close();


	return 0;
}






//for (int i = 0; i < hatch.size(); ++i)
//{
//	std::cout << "Line " << i + 1 << ": (" << hatch[i].first_point.x << ',' << hatch[i].first_point.y;
//	std::cout << ") -> (" << hatch[i].second_point.x << ',' << hatch[i].second_point.y << ")\n";
//}