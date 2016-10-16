#include "solarsystem.h"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

SolarSystem::SolarSystem()
{

}

CelestialBody &SolarSystem::createCelBody(string name, vec3 position, vec3 velocity, double mass)
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
            double dr3 = dr*dr*dr;
            body1.force += G * body1.mass * body2.mass * deltaRVector / (dr3);
            body2.force -= G * body1.mass * body2.mass * deltaRVector / (dr3);

            m_potentialEnergy += body1.force.length() * dr;
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

void SolarSystem::writeToFilePosition(string filename)
{
    filename.append(".txt");

    if(!ofile_position.good())
    {
        ofile_position.open(filename.c_str(), ofstream::out);
        if(!ofile_position.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    for(CelestialBody &body : m_bodies)
    {
        ofile_position << body.name << ":\t[" << setprecision(4) << body.position.x() << ",   " <<
                 body.position.y() << ",   " << body.position.z() << "]" << endl;
    }
}

void SolarSystem::openFile(string filename)
{
    filename.append(".txt");
    ofile.open(filename);
    for(CelestialBody &body : m_bodies)
    {
        ofile << body.name << "\t\t\t\t\t\t";
    }
    ofile << endl;
}

void SolarSystem::writeToFile()
{
    for(CelestialBody &body : m_bodies)
    {
        ofile << setprecision(8) << body.position.x() << setw(20) << body.position.y() << "\t\t";
    }
    ofile << endl;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
