#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace GMHelper
{
	struct GradeStructure
	{
		std::string name = "";
		float Chinese = 0;
		float English = 0;
		float Math = 0;
		float Total = 0;
	};

	class GradeTable
	{
	public:
		void Add(GradeStructure i_grade);

		std::vector<GradeStructure> GetTable();

		std::string GetSingleGradeMax(std::string i_category);
		std::string GetSingleGradeMin(std::string i_category);
		float GetSingleGradeAverage(std::string i_category);
		std::string GetTotalGradeMax();
		std::string GetTotalGradeMin();
		float GetTotalGradeAverage();

		void SortSingle(std::string i_category);
		void SortTotal();

	private:
		std::vector<GradeStructure> m_gradeList;

	};
}