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
    CelestialBody &createCelBody(std::string name, vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();

    double t_final;
    int totalSteps;

    int numberOfBodies() const;
    double totalEnergy() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    vec3 angularMomentum() const;
    void openFileAnimation(std::string filename);
    void openFilePlot(std::string filename);
    void openFilePerihelion(std::string filename);
    void writeToFileAnimation();
    void writeToFilePlot();
    void writeToFilePerihelion(int step);
    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
    std::ofstream ofile_position;
    std::ofstream ofile_animation;
    std::ofstream ofile_plot;
    std::ofstream ofile_perihelion;

    vec3 m_angularMomentum;
    double m_kineticEnergy;
    double m_potentialEnergy;
};

#endif // SOLAR_SYSTEM_H
