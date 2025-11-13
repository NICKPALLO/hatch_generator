export module SVGDocument;

#include<string>
#include <stdexcept>
#include <fstream>

import hatching;


export class SVGDoc
{
public:
	SVGDoc(const std::string& dir_);
	void addLine(const Line_2& line);
	void saveAndClose();
	void openDoc();
	~SVGDoc();

private:
	std::string xml_text;
	std::string dir;
	std::ofstream file;
};