module;
#include <stdexcept>
#include <fstream>
#include <string>

export module SVGDocument;

import hatching;

/**
 * @brief Класс для работы с XML документом.
 */
export class SVGDoc
{
public:
	/**
	* @brief Конструктор класс. Открывает файл
	*
	* @param dir_ Путь к XML файлу.
	*/
	SVGDoc(const std::string& dir_);

	/**
	* @brief Добавляет линию в XML документ
	* @note Документ должен быть открыт
	*/
	void addLine(const Line_2& line);

	/**
	* @brief Помещает сгенерированный текст в XML документ и закрывает его.
	* @note Документ должен быть открыт
	*/
	void saveAndClose();

	/**
	* @brief Открывает документ стандартным приложением
	* @note Документ должен быть закрыт
	*/
	void openDoc();
	/**
	* @brief Деструктор класса. Закрывает файл, если он открыт.
	*/
	~SVGDoc();

private:
	std::string xml_text;
	std::string dir;
	std::ofstream file;
};