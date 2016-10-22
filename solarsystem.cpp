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

            if(body1.name == "Sun" && body2.name == "Mercury")
            {
                body2.angularMomentum = deltaRVector.cross(body2.velocity);
                body1.force *= 1 + 3 * body2.angularMomentum * body2.angularMomentum / (dr * dr * 63239.7263);
                body2.force *= 1 + 3 * body2.angularMomentum * body2.angularMomentum / (dr * dr * 63239.7263);
            }

            if(dr > body2.maxPosition.length())
            {
                body2.maxPosition = deltaRVector;
            }

            if(dr < body2.minPosition.length())
            {
                body2.minPosition = deltaRVector;
            }

            m_angularMomentum += deltaRVector.cross(body1.velocity);
        }
        m_potentialEnergy += body1.force.length() * body1.position.length();
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

void SolarSystem::openFilePlot(string filename)
{
    filename.append(".txt");
    ofile_plot.open(filename);

    for(CelestialBody &body : m_bodies)
    {
        ofile_plot << body.name << "\t\t\t\t\t\t";
    }
    ofile_plot << setiosflags(ios::showpoint | ios::uppercase);
    ofile_plot << endl;
}

void SolarSystem::openFileAnimation(string filename)
{
    filename.append(".xyz");
    ofile_animation.open(filename);
    ofile_plot << setiosflags(ios::showpoint | ios::uppercase);
}

void SolarSystem::writeToFilePlot(int n)
{
    int skip = 100;
    if(n % skip == 0)
    {
        for(CelestialBody &body : m_bodies)
        {
            ofile_plot << setprecision(8) << body.position.x() << setw(15) << body.position.y() <<
                          setw(15) << body.position.z() << "\t";
        }
        ofile_plot << endl;
    }
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

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
