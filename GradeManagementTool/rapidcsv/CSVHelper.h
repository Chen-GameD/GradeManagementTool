#pragma once
#include "rapidcsv/rapidcsv.h"
#include "GradeTable.h"
#include <string>
#include <vector>

namespace CSVHelper
{
	void InsertCSVFromInput(std::string i_path, std::vector<std::string> i_argument);

	void InsertCSVFromGradeTable(std::string i_sourcePath, GMHelper::GradeTable* i_gradeTabel);

	void Output(GMHelper::GradeTable* i_gradeTabel, std::string o_path);
}
