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

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}

void SolarSystem::writeToFile(string filename)
{
    if(!ofile.good())
    {
        ofile.open(filename.c_str(), ofstream::out);
        if(!ofile.good())
        {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    ofile << numberOfBodies() << endl;
    ofile <<"Comment line. " << endl;
    for(CelestialBody &body : m_bodies)
    {
        ofile << "1 " << body.position.x() << " " << body.position.y() << " " <<
                 body.position.y() << endl;
    }
}
