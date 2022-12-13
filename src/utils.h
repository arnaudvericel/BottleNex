#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

template<typename T>
void AddColumn(std::fstream& f, int width, int precision, T element) 
{
    f << std::left << std::setw(width) << std::setprecision(precision) << element << "\t";
};

bool fileExists(const std::string&);
void DisplayLoadingBar(const float);
std::vector<std::string> GetSplittedLine(const std::string& line);

#endif