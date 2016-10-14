#include "solarsystem.h"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

SolarSystem::SolarSystem()
{

}

CelestialBody &SolarSystem::createCelestialBody(string name, vec3 position, vec3 velocity, double mass)
{
    m_bodies.push_back(CelestialBody(name, position, velocity, mass));
    return m_bodies.back();
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    // Reset forces for all bodies
    for(CelestialBody &body : m_bodies)
    {
        body.force.zeros();
    }

    double four_pi_squared = 4 * M_PI * M_PI;
    for(int i = 0; i < numberOfBodies(); i++)
    {
        CelestialBody &body1 = m_bodies[i];
        for(int j = 0; j < numberOfBodies(); j++)
        {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector2 = body2.position - body1.position;
            vec3 deltaRVector1 = body1.position - body2.position;
            double dr = deltaRVector1.length();
            vec3 deltaRVector13 = (deltaRVector1 * deltaRVector1 * deltaRVector1);

            // Calculate the force and potential energy here
            if(j != i)
            {
                body1.force = four_pi_squared / (deltaRVector1 * deltaRVector1 * deltaRVector1);
                body2.force = four_pi_squared / (deltaRVector2 * deltaRVector2 * deltaRVector2);
                //body2.force = four_pi_squared / (deltaRVector * deltaRVector * deltaRVector);
                //body1.force = body1.mass * body2.mass / (deltaRVector * deltaRVector);
                cout << "\ndeltaRVector = " << deltaRVector1 << endl;
                cout << "deltaRVector3 = " << deltaRVector13 << endl;
                cout << "dr = " << dr << endl;
                cout << "Force = " << body1.force << endl;
            }
        }
        m_kineticEnergy += 0.5 * body1.mass * body1.velocity.lengthSquared();
    }
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

void SolarSystem::writeToFile(string filename)
{
    filename.append(".txt");

    if(!ofile.good())
    {
        ofile.open(filename.c_str(), ofstream::out);
        if(!ofile.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    for(CelestialBody &body : m_bodies)
    {
        ofile << body.getName() << ":\t[" << setprecision(4) << body.position.x() << ", " <<
                 body.position.y() << ", " << body.position.z() << "]" << endl;
        //ofile << "Velocity: \t [" << body.velocity.x() << ", " << body.velocity.y() << ", " <<
        //         body.velocity.z() << "]" << endl;
    }
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
