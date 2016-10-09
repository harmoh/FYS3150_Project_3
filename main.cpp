#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"

using namespace std;

int main()
{
    SolarSystem solarSystem;

    solarSystem.createCelestialBody(vec3(1,2,3), vec3(0,0,0), 10);
    solarSystem.createCelestialBody(vec3(9,8,7), vec3(1,M_PI,0), 15);
    solarSystem.createCelestialBody(vec3(2,4,6), vec3(1,1,1), 20);
    solarSystem.createCelestialBody(vec3(3,6,9), vec3(1,0,M_PI), 50);

    solarSystem.writeToFile("solar");

    return 0;
}
