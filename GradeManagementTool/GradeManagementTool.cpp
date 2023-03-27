#include <iostream>
#include "cmdline/cmdline.h"
#include "GradeTable.h"
#include "GradeManagementToolHelper.h"
#include "Tool/tool.h"

int main(int argc, char* argv[])
{
    // argument1: Source File Path / 数据源文件路径
    // argument2: Output File Path(csv/html) / 输出文件路径(csv/html)
    // argument3: Enter directly from the command line / 从命令行直接输入
    // argument4: Import from specified transcript file / 从指定的成绩单文件输入
    // argument5: Process and output source file data / 对源文件数据进行处理并输出

    cmdline::parser a;

    // argument1: source file path
    a.add<std::string>("sFilePath", 's', "Source File Path(support csv/xml)", true, "");
    // argument2: output file path
    a.add<std::string>("oFilePath", 'o', "Output File Path（support csv/html. If the input is "", it will be generated in the current folder by default, and the format is csv)", false, "");
    // argument3: insert from input operation
    a.add<std::string>("iInsert", 'i', "Execute the insert command for the source file, the format of the command is: name 1, Chinese score 1, English score 1, math score 1, name 2, Chinese score 2, English score 2, math score 2...", false, "");
    // argument4: insert from file operation
    a.add<std::string>("fInsert", 'f', "Execute the insert command for the source file, the input format is the file path (supports csv/xml, regardless of the source file format)", false, "");
    // argument5: inquire operation
    a.add<std::string>("inquire", 'q', "Output the results to the command line after performing operations such as query and sorting on the source files. The instruction format is: instruction 1, category 1, instruction 2, category 2...(for example: total,rank,singleMax,chinese)\n\tThe instruction categories are as follows:\n\t1. Single subject result operation: (singleMax/singleMin/singleAverage/singleRank,chinese/english/math)\n\t2. Total score operation: (total,max/min/average/rank)", false, "");

    a.parse_check(argc, argv);

    std::string m_sFilePath = a.get<std::string>("sFilePath");
    std::string m_oFilePaht = a.get<std::string>("oFilePath");
    std::string m_iInsert = a.get<std::string>("iInsert");
    std::string m_fInsert = a.get<std::string>("fInsert");
    std::string m_inquire = a.get<std::string>("inquire");

    if (m_sFilePath != "")
    {
        // The source file must be provided, if not provided, it will be an invalid operation
        if (m_oFilePaht != "")
        {
            // output file
            GMHelper::Output(m_sFilePath, m_oFilePaht);
        }

        if (m_iInsert != "")
        {
            GMHelper::InsertFromInput(m_sFilePath, m_iInsert);
        }

        if (m_fInsert != "")
        {
            GMHelper::InsertFromFile(m_sFilePath, m_fInsert);
        }

        if (m_inquire != "")
        {
            std::vector<std::string> splitResult = Tool::SplitArgument(m_inquire);

            for (size_t index = 0; index < splitResult.size(); index += 2)
            {
                if (splitResult[index] == "singleMax")
                    GMHelper::InquireSingleMax(m_sFilePath, splitResult[index + 1]);
                else if (splitResult[index] == "singleMin")
                    GMHelper::InquireSingleMin(m_sFilePath, splitResult[index + 1]);
                else if (splitResult[index] == "singleAverage")
                    GMHelper::InquireSingleAverage(m_sFilePath, splitResult[index + 1]);
                else if (splitResult[index] == "singleRank")
                    GMHelper::InquireSingleRank(m_sFilePath, splitResult[index + 1]);
                else if (splitResult[index] == "total")
                {
                    if (splitResult[index + 1] == "max")
                        GMHelper::InquireTotalMax(m_sFilePath);
                    else if (splitResult[index + 1] == "min")
                        GMHelper::InquireTotalMin(m_sFilePath);
                    else if (splitResult[index + 1] == "average")
                        GMHelper::InquireTotalAverage(m_sFilePath);
                    else if (splitResult[index + 1] == "rank")
                        GMHelper::InquireTotalRank(m_sFilePath);
                }
                else
                {
                    //error
                    std::cout << "arguments error!" << std::endl;
                }
            }
        }
    }
}
