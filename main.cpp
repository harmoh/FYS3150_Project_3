#include <iostream>
#include <cmath>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"

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

    int totalSteps = 1e5;
    int t_initial = 0;
    double t_final = 1;
    double dt = (t_final - t_initial) / (double) totalSteps;
    cout << "dt = " << dt << endl;
    bool verletIntegrator = true;
    if(verletIntegrator)
    {
        Verlet integratorVerlet(dt);
        solarSystem.openFile("positions");
        for(int step = 0; step < totalSteps; step++)
        {
            integratorVerlet.integrateOneStepVerlet(solarSystem);
            solarSystem.writeToFile();
        }
    }
    else
    {
        Euler integratorEuler(dt);
        solarSystem.openFile("positions");
        for(int step = 0; step < totalSteps; step++)
        {
            integratorEuler.integrateOneStep(solarSystem);
            solarSystem.writeToFile();
        }
    }



    return 0;
}
