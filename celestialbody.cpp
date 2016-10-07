#include "celestialbody.h"

CelestialBody::CelestialBody(vec3 pos, vec3 vel, double mass_temp)
{
    position = pos;
    velocity = vel;
    mass = mass_temp;
}

CelestialBody::CelestialBody(double x, double y, double z, double vx, double vy, double vz, double mass_temp)
{
    position = vec3(x,y,z);
    velocity = vec3(vx,vy,vz);
    mass = mass_temp;
}

void CelestialBody::resetForce()
{
    force.zeros();
}
