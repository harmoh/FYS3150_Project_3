#include "celestialbody.h"

CelestialBody::CelestialBody(std::string name_temp, vec3 pos, vec3 vel, double mass_temp)
{
    name = name_temp;
    position = pos;
    velocity = vel;
    mass = mass_temp;
    maxPosition.zeros();
    minPosition.max();
}

CelestialBody::CelestialBody(std::string name_temp, double x, double y, double z, double vx, double vy, double vz, double mass_temp)
{
    name = name_temp;
    position = vec3(x,y,z);
    velocity = vec3(vx,vy,vz);
    mass = mass_temp;
    maxPosition.zeros();
    minPosition.max();
}

void CelestialBody::resetForce()
{
    force.zeros();
}
