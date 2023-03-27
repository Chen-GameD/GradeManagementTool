#pragma once
#include "tinyxml2/tinyxml2.h"
#include "GradeTable.h"
#include <string>
#include <vector>

namespace XMLHelper
{
	std::string ConvertUTF8ToGB2312(const char* i_utf8);
	void ConvertUTF8ToGB2312ForDoc(tinyxml2::XMLDocument* i_doc);

	std::vector<std::string> GetElementArray(tinyxml2::XMLDocument* i_doc, std::string i_syntax);

	// i_argument[0] = name / i_argument[1] = Chinese score / i_argument[2] = English score / i_argument[3] = math score...
	void InsertXMLFromInput(std::string i_path, std::vector<std::string> i_argument);

	void InsertXMLFromFile(std::string i_sourcePath, std::string i_insertPath);

	void InsertXMLFromGradeTable(std::string i_sourcePath, GMHelper::GradeTable* i_gradeTabel);
}