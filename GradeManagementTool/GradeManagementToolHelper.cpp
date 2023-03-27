#include "GradeManagementToolHelper.h"
#include "Tool/tool.h"

#include <fstream>
#include <windows.h>

// Forward Definition Helper
// ===========================================================================
GMHelper::FILETYPE GetFileTypeByPath(std::string i_path);
GMHelper::FILETYPE GetFileType(std::string i_path);
std::string GetChineseString(std::string i_category);

// Implementation
// ===========================================================================

void GMHelper::OpenSourceFile(GradeTable* i_gradeTable, std::string i_path)
{
	FILETYPE fileType = GetFileTypeByPath(i_path);

	if (fileType == FILETYPE::CSV_TYPE)
	{
		// use csv
		rapidcsv::Document myTable(i_path);
		std::vector<std::string> studentNames = myTable.GetColumn<std::string>("Name");
		std::vector<float> chineaeGrades = myTable.GetColumn<float>("Chinese");
		std::vector<float> englishGrades = myTable.GetColumn<float>("English");
		std::vector<float> mathGrades = myTable.GetColumn<float>("Math");

		for (size_t index = 0; index < studentNames.size(); index++)
		{
			GradeStructure newGradeStruc;
			newGradeStruc.name = studentNames[index];
			newGradeStruc.Chinese = chineaeGrades[index];
			newGradeStruc.English = englishGrades[index];
			newGradeStruc.Math = mathGrades[index];
			newGradeStruc.Total = chineaeGrades[index] + englishGrades[index] + mathGrades[index];

			i_gradeTable->Add(newGradeStruc);
		}
	}
	else if (fileType == FILETYPE::XML_TYPE)
	{
		// use xml
		tinyxml2::XMLDocument doc;
		doc.LoadFile(i_path.c_str());

		std::vector<std::string> studentNames = XMLHelper::GetElementArray(&doc, "Name");
		std::vector<std::string> chineaeGrades = XMLHelper::GetElementArray(&doc, "Chinese");
		std::vector<std::string> englishGrades = XMLHelper::GetElementArray(&doc, "English");
		std::vector<std::string> mathGrades = XMLHelper::GetElementArray(&doc, "Math");

		for (size_t index = 0; index < studentNames.size(); index++)
		{
			GradeStructure newGradeStruc;
			newGradeStruc.name = studentNames[index];
			newGradeStruc.Chinese = (float)atof(chineaeGrades[index].c_str());
			newGradeStruc.English = (float)atof(englishGrades[index].c_str());
			newGradeStruc.Math = (float)atof(mathGrades[index].c_str());
			newGradeStruc.Total = (float)atof(chineaeGrades[index].c_str()) + (float)atof(englishGrades[index].c_str()) + (float)atof(mathGrades[index].c_str());

			i_gradeTable->Add(newGradeStruc);
		}
	}
	else
	{
		// type error
	}
}

GMHelper::FILETYPE GetFileTypeByPath(std::string i_path)
{
	std::string fileType;
	// Only take the last three characters to judge the file type
	fileType = i_path.substr(i_path.length() - 3, i_path.length());

	return GetFileType(fileType);
}

GMHelper::FILETYPE GetFileType(std::string i_type)
{
	// i_type has only three digits, so for some file formats, such as xml and html, I only take the last three digits to determine whether they are equal
	GMHelper::FILETYPE retValue = GMHelper::FILETYPE::NONE;
	if (i_type == "csv")
		retValue = GMHelper::FILETYPE::CSV_TYPE;
	// xml
	if (i_type == "xml")
		retValue = GMHelper::FILETYPE::XML_TYPE;
	// html
	if (i_type == "tml")
		retValue = GMHelper::FILETYPE::HTML_TYPE;

	return retValue;
}

void GMHelper::InsertFromInput(std::string i_path, std::string i_argument)
{
	FILETYPE fileType = GetFileTypeByPath(i_path);

	if (fileType == FILETYPE::CSV_TYPE)
	{
		// csv
		// splitArg[0] = name / splitArg[1] = Chinese score / splitArg[2] = English score / splitArg[3] = math score...
		std::vector<std::string> splitArg = Tool::SplitArgument(i_argument);

		CSVHelper::InsertCSVFromInput(i_path, splitArg);
	}
	else if (fileType == FILETYPE::XML_TYPE)
	{
		// xml
		// splitArg[0] = name / splitArg[1] = Chinese score / splitArg[2] = English score / splitArg[3] = math score...
		std::vector<std::string> splitArg = Tool::SplitArgument(i_argument);

		XMLHelper::InsertXMLFromInput(i_path, splitArg);
	}
	else
	{
		// type error
	}
}

void GMHelper::InsertFromFile(std::string i_sourcePath, std::string i_insertPath)
{
	FILETYPE fileType = GetFileTypeByPath(i_sourcePath);

	if (fileType == FILETYPE::CSV_TYPE)
	{
		GMHelper::GradeTable* insertTable = new GMHelper::GradeTable();
		GMHelper::OpenSourceFile(insertTable, i_insertPath);

		if (insertTable)
		{
			CSVHelper::InsertCSVFromGradeTable(i_sourcePath, insertTable);
		}
	}
	else if (fileType == FILETYPE::XML_TYPE)
	{
		GMHelper::GradeTable* insertTable = new GMHelper::GradeTable();
		GMHelper::OpenSourceFile(insertTable, i_insertPath);

		if (insertTable)
		{
			XMLHelper::InsertXMLFromGradeTable(i_sourcePath, insertTable);
		}
	}
	else
	{
		// type error
	}
}

void GMHelper::InquireSingleMax(std::string i_path, std::string i_category)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	std::string maxGradeString = myTable->GetSingleGradeMax(i_category);

	// direct output
	std::cout << std::endl << GetChineseString(i_category) << "The students with the highest grades are the following students£º" << std::endl;

	std::vector<std::string> splitResult = Tool::SplitArgument(maxGradeString);

	for (size_t index = 0; index < splitResult.size(); index += 2)
	{
		std::cout << splitResult[index] << "\t" << splitResult[index + 1] << std::endl;
	}

}

void GMHelper::InquireSingleMin(std::string i_path, std::string i_category)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	std::string minGradeString = myTable->GetSingleGradeMin(i_category);

	// direct output
	std::cout << std::endl << GetChineseString(i_category) << "The students with the lowest grades are the following students£º" << std::endl;

	std::vector<std::string> splitResult = Tool::SplitArgument(minGradeString);

	for (size_t index = 0; index < splitResult.size(); index += 2)
	{
		std::cout << splitResult[index] << "\t" << splitResult[index + 1] << std::endl;
	}
}

void GMHelper::InquireSingleAverage(std::string i_path, std::string i_category)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	float averageScore = myTable->GetSingleGradeAverage(i_category);

	// direct output
	std::cout << std::endl << GetChineseString(i_category) << "Grade average£º" << std::to_string(averageScore) << std::endl;
}

void GMHelper::InquireSingleRank(std::string i_path, std::string i_category)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	myTable->SortSingle(i_category);

	// Output
	std::cout << std::endl << GetChineseString(i_category) << "The results are sorted as follows:" << std::endl;
	std::cout << "Name\tChinese\tEnglish\tMathematics" << std::endl;

	for (size_t index = 0; index < myTable->GetTable().size(); index++)
	{
		std::cout << myTable->GetTable()[index].name << "\t" << myTable->GetTable()[index].Chinese << "\t" << myTable->GetTable()[index].English << "\t" << myTable->GetTable()[index].Math << std::endl;
	}
}

void GMHelper::InquireTotalMax(std::string i_path)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	std::string maxTotalString = myTable->GetTotalGradeMax();

	// direct output
	std::cout << std::endl << "The students with the highest total score are the following students£º" << std::endl;
	std::cout << "Name\tChinese\tEnglish\tMathematics\tTotal score" << std::endl;

	std::vector<std::string> splitResult = Tool::SplitArgument(maxTotalString);

	for (size_t index = 0; index < splitResult.size(); index += 5)
	{
		std::cout << splitResult[index] << "\t" << splitResult[index + 1] << "\t" << splitResult[index + 2] << "\t" << splitResult[index + 3] << "\t" << splitResult[index + 4] << std::endl;
	}
}

void GMHelper::InquireTotalMin(std::string i_path)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	std::string maxTotalString = myTable->GetTotalGradeMin();

	// direct output
	std::cout << std::endl << "The students with the lowest total score are the following students£º" << std::endl;
	std::cout << "Name\tChinese\tEnglish\tMathematics\tTotal score" << std::endl;

	std::vector<std::string> splitResult = Tool::SplitArgument(maxTotalString);

	for (size_t index = 0; index < splitResult.size(); index += 5)
	{
		std::cout << splitResult[index] << "\t" << splitResult[index + 1] << "\t" << splitResult[index + 2] << "\t" << splitResult[index + 3] << "\t" << splitResult[index + 4] << std::endl;
	}
}

void GMHelper::InquireTotalAverage(std::string i_path)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	float averageScore = myTable->GetTotalGradeAverage();

	// direct output
	std::cout << std::endl << "Average overall score£º" << std::to_string(averageScore) << std::endl;
}

void GMHelper::InquireTotalRank(std::string i_path)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	myTable->SortTotal();

	// Output
	std::cout << std::endl << "The total results are sorted as follows:" << std::endl;
	std::cout << "Name\tChinese\tEnglish\tMathematics\tTotal score" << std::endl;

	for (size_t index = 0; index < myTable->GetTable().size(); index++)
	{
		std::cout << myTable->GetTable()[index].name << "\t" << myTable->GetTable()[index].Chinese << "\t" << myTable->GetTable()[index].English << "\t" << myTable->GetTable()[index].Math << "\t" << myTable->GetTable()[index].Total << std::endl;
	}
}

void GMHelper::Output(std::string i_path, std::string o_path)
{
	GMHelper::GradeTable* myTable = new GMHelper::GradeTable();
	GMHelper::OpenSourceFile(myTable, i_path);

	std::string outputPath = "output.csv";
	if (o_path != "")
		outputPath = o_path;

	FILETYPE fileType = GetFileTypeByPath(outputPath);

	if (fileType == FILETYPE::CSV_TYPE)
	{
		// csv
		CSVHelper::Output(myTable, o_path);
	}
	else if (fileType == FILETYPE::HTML_TYPE)
	{
		// html Just use the C++ output stream to write the file directly, without using any library, so there is no helper created separately
		std::ofstream outputFile;
		outputFile.open(outputPath, std::ios::out | std::ios::trunc);

		outputFile << "<!DOCTYPE html>" << std::endl;
		outputFile << "<html>" << std::endl;
		outputFile << "<table border='1'>" << std::endl;
		outputFile << "<tr>" << std::endl;
		outputFile << "<td>Name</td>" << std::endl;
		outputFile << "<td>Chinese</td>" << std::endl;
		outputFile << "<td>English</td>" << std::endl;
		outputFile << "<td>Math</td>" << std::endl;
		outputFile << "</tr>" << std::endl;

		for (size_t i = 0; i < myTable->GetTable().size(); i++)
		{
			outputFile << "<tr>" << std::endl;
			outputFile << "<td>" << myTable->GetTable()[i].name << "</td>" << std::endl;
			outputFile << "<td>" << myTable->GetTable()[i].Chinese << "</td>" << std::endl;
			outputFile << "<td>" << myTable->GetTable()[i].English << "</td>" << std::endl;
			outputFile << "<td>" << myTable->GetTable()[i].Math << "</td>" << std::endl;
			outputFile << "</tr>" << std::endl;
		}

		outputFile << "</table>" << std::endl;
		outputFile << "</html>" << std::endl;

		outputFile.close();

		std::cout << "Successful output file£º" << o_path << std::endl;

	}
	else
	{
		// type error
		std::cout << "The file format or path is wrong, please check! (The output only supports csv/html)" << std::endl;
	}

}

std::string GetChineseString(std::string i_category)
{
	std::string retValue;
	if (i_category == "chinese")
	{
		retValue = "Chinese";
	}
	if (i_category == "english")
	{
		retValue = "English";
	}
	if (i_category == "math")
	{
		retValue = "Math";
	}

	return retValue;
}