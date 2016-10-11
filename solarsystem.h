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
    CelestialBody &createCelestialBody(std::string name, vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();

    int numberOfBodies() const;
    double totalEnergy() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    void writeToFile(std::string filename);
    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
    std::ofstream ofile;

    vec3 m_angularMomentum;
    double m_kineticEnergy;
    double m_potentialEnergy;
};

#endif // SOLAR_SYSTEM_H
