#include <iostream>
#include "vec3.h"
#include "celestialbody.h"
#include "solarsystem.h"

using namespace std;

int main()
{
    cout << "Hello World! " << endl;
    SolarSystem solarSystem;
    solarSystem.createCelestialBody(vec3(1,0,0), vec3(0,0,0), 15);

    return 0;
}
