#include <iostream>
#include <vector>
#include <string>

import hatching;

import SVGDocument;


/**
 * @brief Выводит линию в стандартный поток вывода.
 *
 * @param line Линия для вывода.
 * @param line_num Индекс линии.
 *        Если равен -1 (значение по умолчанию), индекс не выводится.
 *        В противном случае выводится и линия, и её индекс.
 */
void showLine(const Line_2& line, int line_num = -1)
{
	std::cout << "Line";
	if (line_num != -1)
	{
		std::cout << " " << line_num;
	}
	std::cout << ": (" << line.first_point.x << ',' << line.first_point.y;
	std::cout << ") -> (" << line.second_point.x << ',' << line.second_point.y << ")\n";
}

int main(int argc, char* argv[])
{
	int angle = 45;
	double h = 10;
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "--angle" && i + 1 < argc)
		{
			angle = std::stoi(argv[++i]);
		}
		else if (arg == "--step" && i + 1 < argc)
		{
			h = std::stoi(argv[++i]);
		}
		else
		{
			std::cout << "Unknown flag: " << arg;
		}
	}


	try {
		std::vector<std::vector<Point_2>> contoursPoints = {
			{ {0,0}, {100,0}, {100,100}, {0,100} }, { { 110,100 },{160,100},{160,150},{110,150} }
		};

		SVGDoc doc("../../../test.xml");

		for (const auto& current_cont : contoursPoints)
		{
			std::vector<Line_2> hatch = hatching(current_cont, angle, h);

			for (int i = 0; i < hatch.size(); ++i)
			{
				doc.addLine(hatch[i]);
				showLine(hatch[i],i+1);
			}
			std::cout << std::endl;

			for (int point = 0; point < current_cont.size(); ++point)
			{
				auto p1 = current_cont[point];
				auto p2 = current_cont[(point + 1) % current_cont.size()];
				doc.addLine({ p1 ,p2 });
			}
		}
		doc.saveAndClose();
		doc.openDoc();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}