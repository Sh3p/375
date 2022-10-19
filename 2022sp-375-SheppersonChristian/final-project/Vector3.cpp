/// \file Vector3.cpp
/// \brief Definition of Vector class and any associated global functions.
/// \author Ryan Ganzke
/// \version A04

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Vector3.hpp"

Vector3::Vector3 ()
{
    *this = Vector3(0);
}

Vector3::Vector3 (float xyz)
{
    *this = Vector3(xyz, xyz, xyz);
}

Vector3::Vector3 (float x, float y, float z)
: m_x (x), m_y (y), m_z (z)
{

}

void
Vector3::set (float xyz)
{
    *this = Vector3(xyz);
}

void
Vector3::set (float x, float y, float z)
{
    *this = Vector3(x, y, z);
}

void
Vector3::negate ()
{
    *this = Vector3(-m_x, -m_y, -m_z);
}

float
Vector3::dot (const Vector3& v) const
{
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

float
Vector3::angleBetween (const Vector3& v) const
{
    return std::acos(this->dot(v) / (this->length() * v.length()));
}

Vector3
Vector3::cross (const Vector3& v) const
{
    return Vector3((m_y * v.m_z) - (v.m_y * m_z),  -((m_x * v.m_z) - (v.m_x * m_z)), (m_x * v.m_y) - (v.m_x * m_y));
}

float
Vector3::length () const
{
    return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

void
Vector3::normalize ()
{
    *this = Vector3(m_x / this->length(), m_y / this->length(), m_z / this->length());
}

Vector3&
Vector3::operator+= (const Vector3& v)
{
    *this = Vector3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
    return *this;
}

Vector3&
Vector3::operator-= (const Vector3& v)
{
    *this = Vector3(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
    return *this;
}

Vector3&
Vector3::operator*= (float s)
{
    *this = Vector3(m_x * s, m_y * s, m_z * s);
    return *this;
}

Vector3&
Vector3::operator/= (float s)
{
    *this = Vector3(m_x / s, m_y / s, m_z / s);
    return *this;
}

Vector3
operator+ (const Vector3& v1, const Vector3& v2)
{
    return (Vector3) v1 += v2;
}

Vector3
operator- (const Vector3& v1, const Vector3& v2)
{
    return (Vector3) v1 -= v2;
}

Vector3
operator- (const Vector3& v)
{
    Vector3 negV = v;
    negV.negate();
    return negV;
}

Vector3
operator* (float s, const Vector3& v)
{
    return (Vector3) v *= s;
}

Vector3
operator* (const Vector3& v, float s)
{
    return (Vector3) v *= s;
}

Vector3
operator/ (const Vector3& v, float s)
{
    return (Vector3) v /= s;
}

std::ostream&
operator<< (std::ostream& out, const Vector3& v)
{
    out << std::setprecision(2) << std::fixed
        << std::setw(10) << v.m_x
        << std::setw(10) << v.m_y
        << std::setw(10) << v.m_z;
    return out;
}

bool
operator== (const Vector3& v1, const Vector3& v2)
{
    return fabs(v1.m_x - v2.m_x) < 0.00001f
        && fabs(v1.m_y - v2.m_y) < 0.00001f
        && fabs(v1.m_z - v2.m_z) < 0.00001f;
}