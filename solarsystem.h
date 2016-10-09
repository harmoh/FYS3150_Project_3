#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <fstream>
#include <string>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass);

    int numberOfBodies() const;
    std::vector<CelestialBody> &bodies();
    void writeToFile(std::string filename);

private:
    std::vector<CelestialBody> m_bodies;
    std::ofstream ofile;
};

#endif // SOLAR_SYSTEM_H
