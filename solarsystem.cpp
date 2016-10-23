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
                //body1.force *= 1 + 3 * body2.angularMomentum * body2.angularMomentum / (dr * dr * 63239.7263 * 63239.7263);
                //body2.force *= 1 + 3 * body2.angularMomentum * body2.angularMomentum / (dr * dr * 63239.7263) * 63239.7263;

                body1.force *= 1 + 3 * body2.angularMomentum.lengthSquared() / (deltaRVector.lengthSquared() * 63239.7263 * 63239.7263);
                body2.force *= 1 + 3 * body2.angularMomentum.lengthSquared() / (deltaRVector.lengthSquared() * 63239.7263 * 63239.7263);

                if(body2.counter % 3 == 0)
                {
                    // Check if the *previous* time step was a minimum for the Mercury-Sun distance. I.e. check
                    // if the previous distance is smaller than the current one *and* the previous previous one.
                    if (dr > body2.rPrevious && body2.rPrevious < body2.rPreviousPrevious)
                    {
                        // If we are perihelion, print *previous* angle (in radians) to terminal.
                        double x = body2.previousPosition.x();
                        double y = body2.previousPosition.y();
                        body2.perihelionAngle = atan2(y,x) * 180/M_PI * 3600;
                        writeToFilePerihelion(body2.counter/3);
                    }

                    // Update the helper variables (previous, previousPrevious).
                    body2.rPreviousPrevious = body2.rPrevious;
                    body2.rPrevious = dr;
                    body2.previousPosition = deltaRVector;
                }
            }
            body2.counter++;
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

void SolarSystem::openFilePerihelion(string filename)
{
    filename.append(".txt");
    ofile_perihelion.open(filename);
    ofile_perihelion << setiosflags(ios::showpoint | ios::uppercase);
}

void SolarSystem::openFileAnimation(string filename)
{
    filename.append(".xyz");
    ofile_animation.open(filename);
    ofile_plot << setiosflags(ios::showpoint | ios::uppercase);
}

void SolarSystem::writeToFilePlot()
{
    for(CelestialBody &body : m_bodies)
    {
        ofile_plot << setprecision(8) << body.position.x() << setw(15) << body.position.y() <<
                      setw(15) << body.position.z() << "\t";
    }
    ofile_plot << endl;

}

void SolarSystem::writeToFilePerihelion(int counter)
{
    double step = counter * t_final / totalSteps;
    for(CelestialBody &body : bodies())
    {
        if(body.name == "Mercury")
        {
            ofile_perihelion << step << setw(15) << setprecision(8) << body.perihelionAngle << endl;
        }
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
