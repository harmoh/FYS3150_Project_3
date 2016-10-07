#include "solarsystem.h"

SolarSystem::SolarSystem()
{

}

CelestialBody &SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass)
{
    m_bodies.push_back(CelestialBody(position, velocity, mass));
    return m_bodies.back();
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
