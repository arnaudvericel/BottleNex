#ifndef WRITER_H
#define WRITER_H

#include <string>

class Lane;

class Writer
{
private:
    int vehiclesBraking;
    int vehiclesAccelerating;
    int vehiclesCruising;

    Lane* lane;
    std::string fileName;
    void SetFilename();
    void DeleteFile();

    void InitVehiclesStats();
    void FetchVehiclesStats();
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