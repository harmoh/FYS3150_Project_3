#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "vec3.h"
#include <string>

class CelestialBody
{
public:
    std::string name;
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 force;
    vec3 angularMomentum;
    double mass;

    vec3 minPosition; // Perihelion
    vec3 maxPosition; // Aphelion

    CelestialBody(std::string name_temp, vec3 position, vec3 velocity, double mass);
    CelestialBody(std::string name_temp, double x, double y, double z, double vx, double vy, double vz, double mass);
    void resetForce();
};

#endif // CELESTIAL_BODY_H
