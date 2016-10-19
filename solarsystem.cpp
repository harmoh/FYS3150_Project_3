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

            m_angularMomentum += deltaRVector * body1.velocity;

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

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
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

void SolarSystem::openFileAnimation(string filename)
{
    filename.append(".xyz");
    ofile_animation.open(filename);
}

void SolarSystem::openFilePlot(string filename)
{
    filename.append(".txt");
    ofile_plot.open(filename);

    for(CelestialBody &body : m_bodies)
    {
        ofile_plot << body.name << "\t\t\t\t\t\t";
    }
    ofile_plot << endl;
}

void SolarSystem::writeToFileAnimation()
{
    ofile_animation << numberOfBodies() << endl;
    ofile_animation << "Comment line." << endl;
    for(CelestialBody &body : m_bodies)
    {
        ofile_animation << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}

void SolarSystem::writeToFilePlot()
{
    for(CelestialBody &body : m_bodies)
    {
        ofile_plot << setprecision(8) << body.position.x() << setw(20) << body.position.y() << "\t\t";
    }
    ofile_plot << endl;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
