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

    // Using position in AU and velocity in AU/day from NASA website at 06.10.16 at time 0:00:00 TDB
    solarSystem.createCelBody("Sun", vec3(0, 0, 0), vec3(0, 0, 0), 1.989e30);
    solarSystem.createCelBody("Mercury", vec3(-1.679346790995296E-01, 2.715090795591738E-01, 3.743438522657825E-02),  vec3(-2.946323843638166E-02, -1.286387995076496E-02, 1.595621024945468E-03), 3.302e23);
    solarSystem.createCelBody("Venus", vec3(2.364746340097186E-02, -7.264707703636207E-01, -1.162429192804562E-02), vec3(2.003007598266136E-02, 1.605358871651250E-03, -1.110080568585950E-03), 4.8685e24);
    CelestialBody &earth = solarSystem.createCelBody("Earth", vec3(9.789458703952936E-01, 2.241187148479481E-01, -5.775551813391525E-04), vec3(-4.193234126934759E-03, 1.785582902312583E-02, 4.201814025923851E-05), 5.97e24);
    solarSystem.createCelBody("Mars", vec3(1.084513305385442E+00, -8.661932709102805E-01, -4.522110799925767E-02), vec3(9.234117532090743E-03, 1.326405120321313E-02, 6.857111965381551E-05), 6.4185e23);
    solarSystem.createCelBody("Jupiter", vec3(-5.431992089961208E+00, -3.921857036533175E-01, 1.227190020023220E-01), vec3(3.989288566710636E-04, -6.027119304618441E-03, 6.232465370339122E-05), 1.898e27);
    solarSystem.createCelBody("Saturn", vec3(-2.312150993022660E+00, -9.766310365628753E+00, 2.614170492141576E-01), vec3(5.070977175964075E-03, -1.604296677375475E-04, -1.388277857333026E-04), 5.68319e26);
    solarSystem.createCelBody("Uranus", vec3(1.847790083054035E+01, 7.527197017139850E+00, -2.118049753047129E-01), vec3(-1.565426525523472E-03, 4.601714614579635E-03, 7.497451583187016E-05), 8.681e25);
    solarSystem.createCelBody("Neptune", vec3(2.825277849832495E+01, -9.952223615206286E+00, -4.466083827447455E-01), vec3(9.696626157996110E-04, 4.122115080380716E-03, -4.268843087735500E-05), 1.0241e-26);
    solarSystem.createCelBody("Pluto", vec3(9.397191918215341E+00, -3.182351682516987E+01, 6.866442138641577E-01), vec3(3.016376110629068E-03, 1.381622698537538E-03, -8.603553118791790E-04), 1.307e-22);

    // Using random initial positions
    //solarSystem.createCelBody("Mercury",    vec3(-0.387, 0, 0),     vec3(0, -1.59, 0),      3.3e23);
    //solarSystem.createCelBody("Venus",      vec3(0, -0.723, 0),     vec3(1.18, 0, 0),       4.9e24);
    //solarSystem.createCelBody("Earth",      vec3(1, 0, 0),          vec3(0, 1, 0),          6e24);
    //solarSystem.createCelBody("Mars",       vec3(0, 1.52, 0),       vec3(-0.808, 0, 0),     6.6e23);
    //solarSystem.createCelBody("Jupiter",    vec3(-5.2, 0, 0),       vec3(0, -0.439, 0),     1.9e27);
    //solarSystem.createCelBody("Saturn",     vec3(0, -9.58, 0),      vec3(0.325, 0, 0),      5.5e26);
    //solarSystem.createCelBody("Uranus",     vec3(19.2, 0, 0),       vec3(0, 0.228, 0),      8.8e25);
    //solarSystem.createCelBody("Neptune",    vec3(0, 30.05, 0),      vec3(-0.182, 0, 0),     1.02e-26);
    //solarSystem.createCelBody("Pluto",      vec3(-39.48, 0, 0),     vec3(0, -0.157, 0),     1.46e-22);

    for(CelestialBody &body : solarSystem.bodies())
    {
        double earthUnitVelocity = earth.velocity.length();
        //cout << "earth unit velocity: " << earthUnitVelocity << endl;

        body.velocity *= 2*M_PI / earthUnitVelocity; // Convert from AU/day
        body.mass /= 1.989e30; // Mass of the sun
        //cout << body.name << " velocity vector: " << body.velocity << endl;
    }

    int totalSteps = 1e5;
    int t_initial = 0;
    double t_final = 200;
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
