#ifndef SVGDOCUMENT_H
#define SVGDOCUMENT_H

/**
 * @file SVGDocument.cxx
 * @brief Файл содержащий класс для работы с XML документом.
 */

#include <fstream>
#include "hatching.h"

/**
 * @class SVGDoc
 * @brief Класс для работы с XML документом.
 *
 * Создает XML документ и добавляет на него линии
 * с использованием языка SVG.
 */
class SVGDoc
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



#endif // SVGDOCUMENT_H
