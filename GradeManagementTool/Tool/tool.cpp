#include "tool.h"

std::vector<std::string> Tool::SplitArgument(std::string i_argument)
{
    // Split argument by this format: argument1,argument2,argument3....
    std::vector<std::string> retValue;

    std::string argument = i_argument;
    size_t pos = argument.find(",");
    std::string temp;

    while (pos != argument.npos)
    {
        temp = argument.substr(0, pos);
        retValue.push_back(temp);
        // Remove the split string, and continue to split the rest
        argument = argument.substr(pos + 1, argument.size());
        pos = argument.find(",");
    }

    // add the last paragraph
    temp = argument;
    retValue.push_back(temp);

    return retValue;
}