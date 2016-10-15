#include <iostream>
#include <cmath>
#include <time.h>
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

    int totalSteps = 1e6;
    int t_initial = 0;
    double t_final = 1;
    double dt = (t_final - t_initial) / (double) totalSteps;
    bool verletIntegrator = true;
    string method;
    clock_t time_initial = clock();
    if(verletIntegrator)
    {
        method = "Verlet";
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
        method = "Euler";
        Euler integratorEuler(dt);
        solarSystem.openFile("positions");
        for(int step = 0; step < totalSteps; step++)
        {
            integratorEuler.integrateOneStepEuler(solarSystem);
            solarSystem.writeToFile();
        }
    }
    clock_t time_final = clock();

    cout << "Integrator: " << method << endl;
    cout << "n =\t" << totalSteps << endl;
    cout << "dt =\t" << dt << endl;

    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
