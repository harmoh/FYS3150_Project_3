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

    solarSystem.createCelestialBody("Sun",      vec3(0, 0, 0),    vec3(0, 0, 0),  1);
    solarSystem.createCelestialBody("Earth",    vec3(1, 1, 0),    vec3(0, 0, 0),  3.0e-6);

    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i < (int)(bodies.size()); i++)
    {
        CelestialBody &body = bodies[i];
        cout << "The position of this object is " << body.position << " with velocity " <<
                body.velocity << endl;
    }

    int totalSteps = 10;
    double t_initial = 0;
    double t_final = 1;
    double dt = (t_final - t_initial) / totalSteps;
    Euler integrator(dt);
    for(int step = 0; step < totalSteps; step++)
    {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("position");
    }

    return 0;
}
