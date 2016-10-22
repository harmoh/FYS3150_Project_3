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

int main(int argc, char* argv[])
{
    int methodArg = 0;

    // Read from command line if there are enough arguments
    if(argc <= 1)
    {
        cout << "Bad usage: " << argv[0] <<
                "\nRead output file and n (int) on the same line." << endl;
        exit(1);
    }
    else
    {
        methodArg = atoi(argv[1]); // First command line argument
    }

    SolarSystem solarSystem;

    double t_final = 1; // In years. Set to 1 be default and is used for Sun-Earth system

    if(methodArg == 1)
    {
        solarSystem.createCelBody("Sun", vec3(0, 0, 0), vec3(0, 0, 0), 2e30);
        //solarSystem.createCelBody("Earth", vec3(1, 0, 0), vec3(0, 1.416, 0), 6e24); // Escape velocity
        solarSystem.createCelBody("Earth", vec3(1, 0, 0), vec3(0, 1, 0), 6e24);
    }
    else if(methodArg == 2)
    {
        solarSystem.createCelBody("Sun",        vec3(0, 0, 0),      vec3(0, 0, 0),      2e30);
        solarSystem.createCelBody("Earth",      vec3(1, 0, 0),      vec3(0, 1, 0),      6e24);
        solarSystem.createCelBody("Jupiter",    vec3(-5.2, 0, 0),   vec3(0, -0.439, 0), 1.9e27);

        t_final = 11.9;
    }
    else if(methodArg == 3)
    {
        // Using position in AU and velocity in AU/day from NASA website using Solar System
        // Barycenter as the center of mass. Data is recieved at 06.10.16 at time 0:00:00 TDB.
        solarSystem.createCelBody("Sun",        vec3( 3.583187837707098E-03,  3.347917208376574E-03, -1.601566243263295E-04), vec3(-1.916797473876860E-06,  6.860577040555349E-06,  3.852105421771686E-08), 1.989e30);
        solarSystem.createCelBody("Mercury",    vec3(-1.689638050644479E-01,  2.746185253985868E-01,  3.783565039667143E-02), vec3(-2.941090431599825E-02, -1.400673667979914E-02,  1.552995718374029E-03), 3.302e23);
        solarSystem.createCelBody("Venus",      vec3( 2.261833743605355E-02, -7.233613245242075E-01, -1.122302675795243E-02), vec3( 2.008241010304477E-02,  4.625021426170730E-04, -1.152705875157388E-03), 4.8685e24);
        solarSystem.createCelBody("Earth",      vec3( 9.779167444303752E-01,  2.272281606873612E-01, -1.762900112459768E-04), vec3(-4.140900006551348E-03,  1.671297229409165E-02, -6.071663121998971E-07), 5.97e24);
        solarSystem.createCelBody("Mars",       vec3( 1.083484179334264E+00, -8.630838246913118E-01, -4.481984242527660E-02), vec3( 9.286451652444910E-03,  1.212119447482730E-02,  2.594581334177116E-05), 6.4185e23);
        solarSystem.createCelBody("Jupiter",    vec3(-5.433021216987578E+00, -3.890762583943597E-01,  1.231202671627251E-01), vec3( 4.512629769156300E-04, -7.169976033688688E-03,  1.969934735867556E-05), 1.898e27);
        solarSystem.createCelBody("Saturn",     vec3(-2.313180120049030E+00, -9.763200920369798E+00,  2.618183143745622E-01), vec3( 5.123311296208641E-03, -1.303286396807794E-03, -1.814530920780186E-04), 5.68319e26);
        solarSystem.createCelBody("Uranus",     vec3( 1.847687170457543E+01,  7.530306462979262E+00, -2.114037101346196E-01), vec3(-1.513092405140061E-03,  3.458857885545459E-03,  3.234920926043226E-05), 8.681e25);
        solarSystem.createCelBody("Neptune",    vec3( 2.825174937236003E+01, -9.949114169366872E+00, -4.462071175746522E-01), vec3( 1.021996736183022E-03,  2.979258351346539E-03, -8.531373744879276E-05), 1.0241e26);
        solarSystem.createCelBody("Pluto",      vec3( 9.396162791203736E+00, -3.182040737994854E+01,  6.870454791400117E-01), vec3( 3.068710230865929E-03,  2.387659693669338E-04, -9.029806182733669E-04), 1.307e22);
        t_final = 250;
    }
    else if(methodArg == 4)
    {
        solarSystem.createCelBody("Sun", vec3(0, 0, 0), vec3(0, 0, 0), 2e30);
        solarSystem.createCelBody("Mercury", vec3(0.3075, 0, 0), vec3(0, 1.98, 0), 3.3e23);

        t_final = 100;
        //t_final = 0.2408;
    }
    else
    {
        cout << "Wrong number." << endl;
    }

    double earthUnitVelocity = 1.0;
    for(CelestialBody &body : solarSystem.bodies())
    {
        if(body.name == "Earth")
        {
            earthUnitVelocity = body.velocity.length();
            //cout << "earth unit velocity: " << earthUnitVelocity << endl;
        }
    }

    for(CelestialBody &body : solarSystem.bodies())
    {
        if(methodArg == 3)
        {
            body.velocity *= 2*M_PI / earthUnitVelocity; // Convert from AU/day
            body.mass /= 1.989e30; // Mass of the sun
            //cout << body.name << " velocity vector: " << body.velocity << endl;
        }
        else
        {
            body.velocity *= 2*M_PI; // Convert from AU/day
            body.mass /= 2e30; // Mass of the sun
        }
    }

    int totalSteps = 1e6;
    int t_initial = 0;
    double dt = (t_final - t_initial) / (double) totalSteps; // Final time is set differently for each method
    bool verletIntegrator = true; // Set to false for Euler integrator
    string method;
    clock_t time_initial = clock();
    if(verletIntegrator)
    {
        method = "Verlet";
        Verlet integratorVerlet(dt);
        solarSystem.openFilePlot("positions");
        solarSystem.openFileAnimation("positions");
        for(int step = 0; step < totalSteps; step++)
        {
            integratorVerlet.integrateOneStepVerlet(solarSystem);
            solarSystem.writeToFilePlot();
            //solarSystem.writeToFileAnimation();
        }
        for(CelestialBody &body : solarSystem.bodies())
        {
            // Calculate error for the earth's position when initial position is (1,0,0) and
            // time is for example 1 year.
            if(methodArg == 1 && body.name == "Earth")
            {
                double errorVerlet = body.position.length() - vec3 (1,0,0).length();
                cout << "Error for " << body.name << ":\t" << errorVerlet << endl;
                cout << "Angular momentum:\t" << solarSystem.angularMomentum() << endl;
            }
            if((methodArg == 3 || methodArg == 4) && body.name == "Mercury")
            {
                cout << "Aphelion of " << body.name << " is:\t\t" <<
                        body.maxPosition.length() << " AU" << endl;
                cout << "Perihelion of " << body.name << " is:\t" <<
                        body.minPosition.length() << " AU" << endl;
                cout << "Perihelion angle of " << body.name << " is:\t" <<
                        atan2(body.minPosition.y() , body.minPosition.x()) << "°" << endl;
            }
        }
    }
    else
    {
        method = "Euler";
        Euler integratorEuler(dt);
        solarSystem.openFilePlot("positions");
        solarSystem.openFileAnimation("positions");
        for(int step = 0; step < totalSteps; step++)
        {
            integratorEuler.integrateOneStepEuler(solarSystem);
            solarSystem.writeToFilePlot();
            solarSystem.writeToFileAnimation();
        }
        for(CelestialBody &body : solarSystem.bodies())
        {
            if(body.name == "Earth")
            {
                double errorVerlet = body.position.length() - vec3 (1,0,0).length();
                cout << "Error for " << body.name << ":\t" << errorVerlet << endl;
            }
        }
    }
    clock_t time_final = clock();

    cout << "\nKinetic energy:\t\t" << solarSystem.kineticEnergy() << endl;
    cout << "Potential energy:\t" << solarSystem.potentialEnergy() << endl;
    cout << "Total energy:\t\t" << solarSystem.totalEnergy() << endl;

    cout << "\nIntegrator: " << method << endl;
    cout << "Final time: " << t_final << " year(s)." << endl;
    cout << "n =\t" << totalSteps << endl;
    cout << "dt =\t" << dt << endl;

    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
