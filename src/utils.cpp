#include <sys/stat.h>
#include <iostream>
#include <sstream>

#include "utils.h"

bool fileExists(const std::string& fileName)
{
    struct stat buffer;   
    return (stat (fileName.c_str(), &buffer) == 0);
}

void DisplayLoadingBar(const float progress)
{
    int barWidth = 100;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i=0; i<barWidth; i++) {
        if (i<pos) { std::cout << "="; }
        else if (i==pos) { std::cout << ">"; }
        else { std::cout << " "; }
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();

    if ((int)progress == 1) { std::cout << std::endl; }
}

std::vector<std::string> GetSplittedLine(const std::string& line)
{
    std::istringstream ssLine(line);
    std::string elem;
    std::vector<std::string> toReturn;
 
    while (getline(ssLine, elem, ';'))
    {
        toReturn.push_back(elem);
    }

    return toReturn;
}
