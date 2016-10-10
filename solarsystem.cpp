#include "solarsystem.h"

using namespace std;

SolarSystem::SolarSystem()
{

}

CelestialBody &SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass)
{
    m_bodies.push_back(CelestialBody(position, velocity, mass));
    return m_bodies.back();
}

int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

void SolarSystem::writeToFile(string filename)
{
    filename.append(".txt");

    if(ofile.good())
    {
        ofile.open(filename.c_str(), ofstream::out);
        if(!ofile.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    ofile << "Number of bodies: " << numberOfBodies() << endl;
    ofile << "--------------------------------" << endl;
    ofile << "Position: \t Velocity: " << endl;
    for(CelestialBody &body : m_bodies)
    {
        ofile << "[" << body.position.x() << ", " << body.position.y() << ", " <<
                 body.position.z() << "] \t ";
        ofile << "[" << body.velocity.x() << ", " << body.velocity.y() << ", " <<
                 body.velocity.z() << "]" << endl;
    }
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
