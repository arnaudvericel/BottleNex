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
    void WriteHeader();

    void InitVehiclesStats();
    void FetchVehiclesStats();

public:
    Writer();
    ~Writer() = default;

    void WriteStep(const float);
    void Init(Lane*);
    
    float GetMeanDensity() const;
    float GetMeanDistance() const;
    float GetMeanVelocity() const;
    std::string GetFileName() const;
    Lane* GetLane() const;
};

#endif