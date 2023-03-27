#pragma once

#include "tinyxml2/XMLHelper.h"
#include "rapidcsv/CSVHelper.h"
#include "GradeTable.h"

namespace GMHelper
{
	enum class FILETYPE
	{
		NONE,
		CSV_TYPE,
		XML_TYPE,
		HTML_TYPE
	};

	void OpenSourceFile(GradeTable* i_gradeTable, std::string i_path);

	// i_path: file path;
	// i_argument: Input parameters (name (string), Chinese score (float), English score (float), math score (float))
	void InsertFromInput(std::string i_path, std::string i_argument);
	void InsertFromFile(std::string i_sourcePath, std::string i_insertPath);

	void InquireSingleMax(std::string i_path, std::string i_category);
	void InquireSingleMin(std::string i_path, std::string i_category);
	void InquireSingleAverage(std::string i_path, std::string i_category);
	void InquireSingleRank(std::string i_path, std::string i_category);
	void InquireTotalMax(std::string i_path);
	void InquireTotalMin(std::string i_path);
	void InquireTotalAverage(std::string i_path);
	void InquireTotalRank(std::string i_path);

	void Output(std::string i_path, std::string o_path = "");

}