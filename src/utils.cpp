#include <sys/stat.h>

#include "utils.h"

bool fileExists(const std::string& fileName)
{
    struct stat buffer;   
    return (stat (fileName.c_str(), &buffer) == 0);
}
