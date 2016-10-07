#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "celestialbody.h"
#include <vector>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass);

    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
};

#endif // SOLAR_SYSTEM_H
