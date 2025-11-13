#include <iostream>
#include <vector>
#include <string>
#include <fstream>

import hatching;

import SVGDocument;



int main()
{
	//исходные данные
	std::vector<std::vector<Point_2>> contoursPoints = {
		{ {0,0}, {100,0}, {100,100}, {0,100} }
	};
	double angle = 45;
	double h = 20;

	SVGDoc doc("../../../test.xml");

	for (int cur_cont = 0; cur_cont < contoursPoints.size(); ++cur_cont)
	{
		std::vector<Line_2> hatch = hatching(contoursPoints[cur_cont], angle, h);

		for (const auto& line : hatch)
		{
			doc.addLine(line);
		}
		
		for (int point = 0; point < contoursPoints[cur_cont].size(); ++point)
		{
			auto p1 = contoursPoints[cur_cont][point];
			auto p2 = contoursPoints[cur_cont][(point + 1) % contoursPoints[cur_cont].size()];


			doc.addLine({ p1 ,p2 });
		}
	}
	doc.saveAndClose();

	return 0;
}






//for (int i = 0; i < hatch.size(); ++i)
//{
//	std::cout << "Line " << i + 1 << ": (" << hatch[i].first_point.x << ',' << hatch[i].first_point.y;
//	std::cout << ") -> (" << hatch[i].second_point.x << ',' << hatch[i].second_point.y << ")\n";
//}