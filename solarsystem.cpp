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

    double G = 4 * M_PI * M_PI;
    for(int i = 0; i < numberOfBodies(); i++)
    {
        CelestialBody &body1 = m_bodies[i];
        for(int j = i+1; j < numberOfBodies(); j++)
        {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body2.position - body1.position;
            double dr = deltaRVector.length();
            body1.force += G * body1.mass * body2.mass * deltaRVector / (dr*dr*dr);
            body2.force -= G * body1.mass * body2.mass * deltaRVector / (dr*dr*dr);
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
        ofile << body.getName() << ":\t[" << setprecision(4) << body.position.x() << ",   " <<
                 body.position.y() << ",   " << body.position.z() << "]" << endl;
        //ofile << "Velocity: \t [" << body.velocity.x() << ", " << body.velocity.y() << ", " <<
        //         body.velocity.z() << "]" << endl;
    }
}

void SolarSystem::openFileEarth()
{
    string filenameEarth = "earth.txt";
    ofile_earth.open(filenameEarth);
    CelestialBody &body = m_bodies[1];
    ofile_earth << body.getName() << "\t\tPosition:" << endl;
}

void SolarSystem::writeToFileEarth(int n)
{
    CelestialBody &body = m_bodies[1];
    ofile_earth << setprecision(8) << body.position.x() <<
                   setw(15) << body.position.y() << setw(15) << body.position.z() << endl;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
