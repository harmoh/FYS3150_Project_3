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

    // Using position in AU and velocity compared to the earth

    solarSystem.createCelBody("Sun",        vec3(0, 0, 0),          vec3(0, 0, 0),          2.0e30);
    //solarSystem.createCelBody("Mercury",    vec3(-0.387, 0, 0),     vec3(0, -1.59, 0),      3.3e23);
    //solarSystem.createCelBody("Venus",      vec3(0, -0.723, 0),     vec3(1.18, 0, 0),       4.9e24);
    solarSystem.createCelBody("Earth",      vec3(1, 0, 0),          vec3(0, 1, 0),          6e24);
    //solarSystem.createCelBody("Mars",       vec3(0, 1.52, 0),       vec3(-0.808, 0, 0),     6.6e23);
    solarSystem.createCelBody("Jupiter",    vec3(-5.2, 0, 0),       vec3(0, -0.439, 0),     1.9e27);
    //solarSystem.createCelBody("Saturn",     vec3(0, -9.58, 0),      vec3(0.325, 0, 0),      5.5e26);
    //solarSystem.createCelBody("Uranus",     vec3(19.2, 0, 0),       vec3(0, 0.228, 0),      8.8e25);
    //solarSystem.createCelBody("Neptune",    vec3(0, 30.05, 0),      vec3(-0.182, 0, 0),     1.02e-26);
    //solarSystem.createCelBody("Pluto",      vec3(-39.48, 0, 0),     vec3(0, -0.157, 0),     1.46e-22);

    for(CelestialBody &body : solarSystem.bodies())
    {
        body.velocity *= 2*M_PI;
        body.mass /= 2e30;
    }

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
        for(CelestialBody &body : solarSystem.bodies())
        {
            if(body.name == "Earth")
            {
                double errorVerlet = body.position.length() - vec3 (1,0,0).length();
                cout << "Error verlet for " << body.name << ": " << errorVerlet << endl;
            }
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
        for(CelestialBody &body : solarSystem.bodies())
        {
            if(body.name == "Earth")
            {
                double errorVerlet = body.position.length() - vec3 (1,0,0).length();
                cout << "Error euler for " << body.name << ": " << errorVerlet << endl;
            }
        }
    }
    clock_t time_final = clock();

    cout << "Kinetic energy: " << solarSystem.kineticEnergy() << endl;
    cout << "Potential energy: " << solarSystem.potentialEnergy() << endl;
    cout << "Total energy: " << solarSystem.totalEnergy() << endl;

    cout << "Integrator: " << method << endl;
    cout << "n =\t" << totalSteps << endl;
    cout << "dt =\t" << dt << endl;

    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
