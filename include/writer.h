#ifndef WRITER_H
#define WRITER_H

#include <string>

class Lane;

class Writer
{
private:
    Lane* lane;
    std::string fileName;
    void SetFilename();
    void DeleteFile();

    float GetMeanDensity() const;
    float GetMeanDistance() const;
    float GetMeanVelocity() const;

public:
    Writer();
    ~Writer() = default;
    void WriteStep(const float);
    void WriteHeader();
    void Init(Lane*);
};

#endif