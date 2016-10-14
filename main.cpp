#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include "euler.h"

using namespace std;
ofstream ofile;

int main()
{
    SolarSystem solarSystem;

    solarSystem.createCelestialBody("Sun",      vec3(0, 0, 0),    vec3(0, 0, 0),  1);
    solarSystem.createCelestialBody("Earth",    vec3(1, 0, 0),    vec3(0, 2*M_PI, 0),  3.0e-6);

//    vector<CelestialBody> &bodies = solarSystem.bodies();
//
//    for(int i = 0; i < (int)(bodies.size()); i++)
//    {
//        CelestialBody &body = bodies[i];
//        cout << "The position of this object is " << body.position << " with velocity " <<
//                body.velocity << endl;
//    }

    int totalSteps = 10000;
    int t_initial = 0;
    int t_final = 1;
    double dt = (t_final - t_initial) / (double) totalSteps;
    cout << "dt = " << dt << endl;
    Euler integrator(dt);
    solarSystem.openFileEarth();
    for(int step = 0; step < totalSteps; step++)
    {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("position");
        solarSystem.writeToFileEarth(step);
    }

    return 0;
}
