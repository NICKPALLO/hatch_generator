module hatching;



std::pair<double, double> findBmin(const std::vector<Point_2>& points, const double k)
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



std::vector<Line_2> hatching(const std::vector<Point_2>& contour, double angle, double h)
{
	double angle_rad = angle * pi / 180;
	double k = tan(angle_rad);
	double delta_b = h / cos(angle_rad);

	auto b_pair = findBmin(contour, k);
	double b_min = b_pair.first;
	double b_max = b_pair.second;


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


	return hatch;
}
