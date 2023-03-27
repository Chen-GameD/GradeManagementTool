#include "GradeTable.h"
#include <algorithm>

// Helper
// ========================================================
bool AscendingOrderSort_C(GMHelper::GradeStructure a, GMHelper::GradeStructure b);
bool AscendingOrderSort_E(GMHelper::GradeStructure a, GMHelper::GradeStructure b);
bool AscendingOrderSort_M(GMHelper::GradeStructure a, GMHelper::GradeStructure b);
bool AscendingOrderSort_T(GMHelper::GradeStructure a, GMHelper::GradeStructure b);

void GMHelper::GradeTable::Add(GradeStructure i_grade)
{
	m_gradeList.push_back(i_grade);
}

std::vector<GMHelper::GradeStructure> GMHelper::GradeTable::GetTable()
{
	return m_gradeList;
}

std::string GMHelper::GradeTable::GetSingleGradeMax(std::string i_category)
{
	// The format of retValue is: name, grade, name, grade...
	std::string retValue = "";
	std::vector<float> tempScoreList;
	std::vector<std::string> nameList;
	if (i_category == "chinese")
	{
		tempScoreList.push_back(m_gradeList[0].Chinese);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].Chinese > tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].Chinese);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].Chinese == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].Chinese);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}
	if (i_category == "english")
	{
		tempScoreList.push_back(m_gradeList[0].English);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].English > tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].English);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].English == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].English);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}
	if (i_category == "math")
	{
		tempScoreList.push_back(m_gradeList[0].Math);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].Math > tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].Math);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].Math == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].Math);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}

	for (size_t index = 0; index < nameList.size(); index++)
	{
		retValue += nameList[index] + ",";
		if (index != nameList.size() - 1)
			retValue += std::to_string(tempScoreList[index]) + ",";
		else
			retValue += std::to_string(tempScoreList[index]);
	}

	return retValue;
}

std::string GMHelper::GradeTable::GetSingleGradeMin(std::string i_category)
{
	// The format of retValue is: name, grade, name, grade...
	std::string retValue = "";
	std::vector<float> tempScoreList;
	std::vector<std::string> nameList;
	if (i_category == "chinese")
	{
		tempScoreList.push_back(m_gradeList[0].Chinese);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].Chinese < tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].Chinese);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].Chinese == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].Chinese);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}
	if (i_category == "english")
	{
		tempScoreList.push_back(m_gradeList[0].English);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].English < tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].English);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].English == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].English);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}
	if (i_category == "math")
	{
		tempScoreList.push_back(m_gradeList[0].Math);
		nameList.push_back(m_gradeList[0].name);

		for (size_t index = 1; index < m_gradeList.size(); index++)
		{
			if (m_gradeList[index].Math < tempScoreList[0])
			{
				// reset list
				tempScoreList.clear();
				nameList.clear();

				tempScoreList.push_back(m_gradeList[index].Math);
				nameList.push_back(m_gradeList[index].name);
			}
			else if (m_gradeList[index].Math == tempScoreList[0])
			{
				tempScoreList.push_back(m_gradeList[index].Math);
				nameList.push_back(m_gradeList[index].name);
			}
		}
	}

	for (size_t index = 0; index < nameList.size(); index++)
	{
		retValue += nameList[index] + ",";
		if (index != nameList.size() - 1)
			retValue += std::to_string(tempScoreList[index]) + ",";
		else
			retValue += std::to_string(tempScoreList[index]);
	}

	return retValue;
}

float GMHelper::GradeTable::GetSingleGradeAverage(std::string i_category)
{
	std::string retValue = "";
	float totalScore = 0;
	float averageScore = 0;

	if (i_category == "chinese")
	{
		for (size_t index = 0; index < m_gradeList.size(); index++)
		{
			totalScore += m_gradeList[index].Chinese;
		}
		averageScore = totalScore / m_gradeList.size();
	}
	if (i_category == "english")
	{
		for (size_t index = 0; index < m_gradeList.size(); index++)
		{
			totalScore += m_gradeList[index].English;
		}
		averageScore = totalScore / m_gradeList.size();
	}
	if (i_category == "math")
	{
		for (size_t index = 0; index < m_gradeList.size(); index++)
		{
			totalScore += m_gradeList[index].Math;
		}
		averageScore = totalScore / m_gradeList.size();
	}

	return averageScore;
}

void GMHelper::GradeTable::SortSingle(std::string i_category)
{
	if (i_category == "chinese")
	{
		std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_C);
	}
	if (i_category == "english")
	{
		std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_E);
	}
	if (i_category == "math")
	{
		std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_M);
	}
}

bool AscendingOrderSort_C(GMHelper::GradeStructure a, GMHelper::GradeStructure b)
{
	return a.Chinese > b.Chinese;
}

bool AscendingOrderSort_E(GMHelper::GradeStructure a, GMHelper::GradeStructure b)
{
	return a.English > b.English;
}

bool AscendingOrderSort_M(GMHelper::GradeStructure a, GMHelper::GradeStructure b)
{
	return a.Math > b.Math;
}

bool AscendingOrderSort_T(GMHelper::GradeStructure a, GMHelper::GradeStructure b)
{
	return a.Total > b.Total;
}

std::string GMHelper::GradeTable::GetTotalGradeMax()
{
	// The format of retValue is: name, grade, name, grade...
	std::string retValue = "";

	std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_T);

	float tempTotalScore = m_gradeList[0].Total;
	retValue = m_gradeList[0].name + "," 
		+ std::to_string(m_gradeList[0].Chinese) + "," 
		+ std::to_string(m_gradeList[0].English) + "," 
		+ std::to_string(m_gradeList[0].English) + "," 
		+ std::to_string(m_gradeList[0].Total);

	for (size_t index = 1; index < m_gradeList.size(); index++)
	{
		if (m_gradeList[index].Total == tempTotalScore)
		{
			retValue += "," + m_gradeList[index].name + "," 
				+ std::to_string(m_gradeList[index].Chinese) + "," 
				+ std::to_string(m_gradeList[index].English) + "," 
				+ std::to_string(m_gradeList[index].English) + "," 
				+ std::to_string(m_gradeList[0].Total);
		}
		else
		{
			break;
		}
	}

	return retValue;
}

std::string GMHelper::GradeTable::GetTotalGradeMin()
{
	// The format of retValue is: name, grade, name, grade...
	std::string retValue = "";

	std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_T);

	float tempTotalScore = m_gradeList.back().Total;
	retValue = m_gradeList.back().name + ","
		+ std::to_string(m_gradeList.back().Chinese) + ","
		+ std::to_string(m_gradeList.back().English) + ","
		+ std::to_string(m_gradeList.back().English) + ","
		+ std::to_string(m_gradeList.back().Total);

	for (size_t index = m_gradeList.size() - 2; index > 0; index--)
	{
		if (m_gradeList[index].Total == tempTotalScore)
		{
			retValue += "," + m_gradeList[index].name + ","
				+ std::to_string(m_gradeList[index].Chinese) + ","
				+ std::to_string(m_gradeList[index].English) + ","
				+ std::to_string(m_gradeList[index].English) + ","
				+ std::to_string(m_gradeList[0].Total);
		}
		else
		{
			break;
		}
	}

	return retValue;
}

float GMHelper::GradeTable::GetTotalGradeAverage()
{
	std::string retValue = "";
	float totalScore = 0;
	float averageScore = 0;

	for (size_t index = 0; index < m_gradeList.size(); index++)
	{
		totalScore += m_gradeList[index].Total;
	}
	averageScore = totalScore / m_gradeList.size();

	return averageScore;
}

void GMHelper::GradeTable::SortTotal()
{
	std::sort(m_gradeList.begin(), m_gradeList.end(), AscendingOrderSort_T);
}