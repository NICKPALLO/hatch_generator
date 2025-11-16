#include "SVGDocument.h"
#include <stdexcept>
#include <string>

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
