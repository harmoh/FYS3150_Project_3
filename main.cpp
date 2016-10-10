#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include "euler.h"

using namespace std;

int main()
{
    SolarSystem solarSystem;

    solarSystem.createCelestialBody(vec3(0,0,0), vec3(0,0,0), 1.0);
    solarSystem.createCelestialBody(vec3(1,0,0), vec3(0, 2*M_PI, 0), 3e-6);

    int totalSteps = 1000;
    double dt = 0.001;
    Euler integrator(dt);
    for(int step = 0; step < totalSteps; step++)
    {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("solar");
    }

    return 0;
}
