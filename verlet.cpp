#include "verlet.h"
#include "solarsystem.h"

Verlet::Verlet(double dt) :
    m_dt(dt)
{

}

void Verlet::integrateOneStepVerlet(SolarSystem &system)
{
    system.calculateForcesAndEnergy();

    for(CelestialBody &body : system.bodies())
    {
        body.acceleration = body.force / body.mass;
        body.position += m_dt * body.velocity + body.acceleration * m_dt * m_dt / 2;
        body.velocity += (body.acceleration + body.acceleration) * m_dt / 2;
    }
}
