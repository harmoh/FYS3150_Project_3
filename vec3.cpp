#include "vec3.h"
#include <cmath>
#include <iostream>
using namespace std;

vec3::vec3()
{
    zeros();
}
vec3::vec3(double x, double y, double z)
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

double vec3::lengthSquared()
{
    // Returns the square of the length (or norm) of the vector
    return components[0]*components[0]+components[1]*components[1]+components[2]*components[2];
}

double vec3::length()
{
    // Returns the length (or norm) of the vector
    return sqrt(lengthSquared());
}

void vec3::print()
{
    cout << "[" << components[0] << ", " << components[1] << ", " << components[2] << "]" << endl;
}

void vec3::printName(string name)
{
    cout << name << ": ";
    print();
}

void vec3::zeros()
{
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

vec3 &vec3::operator+=(double rhs)
{
    components[0] += rhs;
    components[1] += rhs;
    components[2] += rhs;
    return *this;
}

vec3 &vec3::operator+=(vec3 rhs)
{
    components[0] += rhs[0];
    components[1] += rhs[1];
    components[2] += rhs[2];
    return *this;
}

vec3 &vec3::operator*=(double rhs)
{
    components[0] *= rhs;
    components[1] *= rhs;
    components[2] *= rhs;
    return *this;
}

vec3 &vec3::operator*=(vec3 rhs)
{
    components[0] *= rhs[0];
    components[1] *= rhs[1];
    components[2] *= rhs[2];
    return *this;
}

vec3 &vec3::operator-=(double rhs)
{
    components[0] -= rhs;
    components[1] -= rhs;
    components[2] -= rhs;
    return *this;
}

vec3 &vec3::operator-=(vec3 rhs)
{
    components[0] -= rhs[0];
    components[1] -= rhs[1];
    components[2] -= rhs[2];
    return *this;
}

vec3 &vec3::operator/=(double rhs)
{
    components[0] /= rhs;
    components[1] /= rhs;
    components[2] /= rhs;
    return *this;
}

vec3 &vec3::operator/=(vec3 rhs)
{
    components[0] /= rhs[0];
    components[1] /= rhs[1];
    components[2] /= rhs[2];
    return *this;
}
