/**
 * @file SVGDocument.cxx
 * @brief Файл содержащий класс для работы с XML документом.
 */

module;
#include <stdexcept>
#include <fstream>
#include <string>

export module SVGDocument;

import hatching;

/**
 * @class SVGDoc
 * @brief Класс для работы с XML документом.
 *
 * Создает XML документ и добавляет на него линии
 * с использованием языка SVG.
 */
export class SVGDoc
{
public:
	/**
    * @brief Конструктор класса. Открывает файл.
	*
	* @param dir_ Путь к XML файлу.
	*/
	SVGDoc(const std::string& dir_);

	/**
    * @brief Добавляет линию в XML документ.
    *
    * @param Line_2 линия, которую необходимо добавить в документ.
    *
    * @note Документ должен быть открыт.
	*/
	void addLine(const Line_2& line);

	/**
	* @brief Помещает сгенерированный текст в XML документ и закрывает его.
    * @note Документ должен быть открыт.
	*/
	void saveAndClose();

	/**
    * @brief Открывает документ стандартным приложением.
    * @note Документ должен быть закрыт.
	*/
	void openDoc();
	/**
	* @brief Деструктор класса. Закрывает файл, если он открыт.
	*/
	~SVGDoc();

private:
	std::string xml_text;
	std::string dir;
    std::ofstream file; ///<Файл
};

SVGDoc::SVGDoc(const std::string& dir_) : dir(dir_)
{
    file.open(dir);
    if (!file.is_open())
    {
        throw std::runtime_error("xml file is not open");
    }
    xml_text = "<svg xmlns = \"http://www.w3.org/2000/svg\"\n"
               "width = \"100%\" height = \"100%\"\n"
               "viewBox = \"0 0 400 200\"\n"
               "version = \"1.1\" >\n\n";
}

void SVGDoc::addLine(const Line_2& line)
{
    if (file.is_open())
    {
        std::string line_text = "<line x1 = \"" + std::to_string(line.first_point.x) +
                                "\" y1 = \"" + std::to_string(line.first_point.y) + "\" x2 = \"" +
                                std::to_string(line.second_point.x) + "\" y2 = \"" + std::to_string(line.second_point.y) +
                                "\" \nstroke = \"#000000\" stroke-width = \"1\" stroke-linecap = \"round\" /> \n";
        xml_text += line_text;
    }
    else
    {
        throw std::runtime_error("xml file is not open");
    }
}

void SVGDoc::saveAndClose()
{
    if (file.is_open())
    {
        xml_text += "</svg>";
        file << xml_text;
        file.close();
    }
    else
    {
        throw std::runtime_error("xml file is not open");
    }
}

void SVGDoc::openDoc()
{
#if defined(_WIN32)
    system(("start " + dir).c_str());
#elif defined(__APPLE__)
    system(("open " + dir).c_str());
#elif defined(__linux__)
    system(("xdg-open " + dir).c_str());
#endif
}

SVGDoc::~SVGDoc()
{
    if (file.is_open())
    {
        file.close();
    }
}
