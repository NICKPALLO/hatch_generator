/**
 * @file main.cpp
 * @brief Основной файл программы для генерации штриховки и сохранения результата в SVG.
 *
 * Выполняет разбор аргументов командной строки (--angle, --step), создаёт набор контуров,
 * генерирует линии штриховки с помощью функции hatching(), выводит их в консоль и
 * сохраняет в SVG-документ через класс SVGDoc.
 */
/**
 * @mainpage Генерация штриховки прямоугольников
 *
 * Этот проект демонстрирует:
 *  - Создание линий штриховки для заданных контуров прямоугольников с помощью функции hatching(),
 *  - Сохранение результата в SVG-документ через класс SVGDoc,
 *  - Вывод линий на экран.
 */


#include <iostream>
#include <vector>
#include <string>

import hatching;

import SVGDocument;

extern template class std::vector<Point_2>;
extern template class std::vector<Line_2>;

/**
 * @brief Функция, которая выводит линию в стандартный поток вывода.
 *
 * @param line Линия для вывода.
 * @param line_num Индекс линии.
 *        Если равен -1 (значение по умолчанию), индекс не выводится.
 *        В противном случае выводится и линия, и её индекс.
 *
 * @code
 * Line_2 l{{0,0},{10,10}};
 * showLine(l);        // Вывод: Line: (0,0) -> (10,10)
 * showLine(l, 3);     // Вывод: Line 3: (0,0) -> (10,10)
 * @endcode
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

/**
 * @brief Точка входа в программу.
 *
 * Разбирает аргументы командной строки:
 * - --angle <число> : угол наклона штриховки (по умолчанию 45)
 * - --step <число> : шаг штриховки (по умолчанию 10)
 *
 * Создает контуры, генерирует линии штриховки с помощью функции hatching(),
 * выводит их на экран и сохраняет в XML-документ через SVGDoc.
 *
 * @return 0 при успешном выполнении программы.
 */
int main(int argc, char* argv[])
{
	int angle = 45;
	double h = 10;
	for (int i = 1; i < argc; ++i)
	{
        std::string_view arg = argv[i];
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

        SVGDoc doc("test.xml");

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
