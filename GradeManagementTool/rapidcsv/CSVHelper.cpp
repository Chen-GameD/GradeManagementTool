#include "CSVHelper.h"

void CSVHelper::InsertCSVFromInput(std::string i_path, std::vector<std::string> i_argument)
{

	std::ofstream sourceFile;
	sourceFile.open(i_path, std::ios::app);

	for (size_t index = 0; index < i_argument.size(); index += 4)
	{
		sourceFile << i_argument[index] << "," << i_argument[index + 1] << "," << i_argument[index + 2] << "," << i_argument[index + 3] << std::endl;
		std::cout << "insert: <" << i_argument[index] << "," << i_argument[index + 1] << "," << i_argument[index + 2] << "," << i_argument[index + 3] << "> to " << i_path << std::endl;
	}
}

void CSVHelper::InsertCSVFromGradeTable(std::string i_sourcePath, GMHelper::GradeTable* i_gradeTabel)
{
	// insert file type is csv
	std::ofstream sourceFile;
	sourceFile.open(i_sourcePath, std::ios::app);

	for (size_t index = 0; index < i_gradeTabel->GetTable().size(); index++)
	{
		sourceFile << i_gradeTabel->GetTable()[index].name << "," << i_gradeTabel->GetTable()[index].Chinese << "," << i_gradeTabel->GetTable()[index].English << "," << i_gradeTabel->GetTable()[index].Math << std::endl;
		std::cout << "insert: <" << i_gradeTabel->GetTable()[index].name << "," << i_gradeTabel->GetTable()[index].Chinese << "," << i_gradeTabel->GetTable()[index].English << "," << i_gradeTabel->GetTable()[index].Math << "> to " << i_sourcePath << std::endl;
	}
}

void CSVHelper::Output(GMHelper::GradeTable* i_gradeTabel, std::string o_path)
{
	std::ofstream outputFile;
	outputFile.open(o_path, std::ios::out | std::ios::trunc);

	outputFile << "Name" << "," << "Chinese" << "," << "English" << "," << "Math" << std::endl;

	for (size_t i = 0; i < i_gradeTabel->GetTable().size(); i++)
	{
		outputFile << i_gradeTabel->GetTable()[i].name << "," << i_gradeTabel->GetTable()[i].Chinese << "," << i_gradeTabel->GetTable()[i].English << "," << i_gradeTabel->GetTable()[i].Math << std::endl;
	}

	outputFile.close();

	std::cout << "Successful output file£º" << o_path << std::endl;
}