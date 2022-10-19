/// \brief Matrix4.cpp
/// \brief Definitions of Matrix4 class member and associated global functions.
/// \author Ryan Ganzke
/// \version A07

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Matrix4.hpp"

Matrix4::Matrix4 ()
: m_right (Vector4 (1.0f, 0.0f, 0.0f, 0.0f)), m_up (Vector4 (0.0f, 1.0f, 0.0f, 0.0f)), m_back (Vector4 (0.0f, 0.0f, 1.0f, 0.0f)), m_translation (Vector4 (0.0f, 0.0f, 0.0f, 1.0f))
{

}

Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
	const Vector4& back, const Vector4& translation)
: m_right (right), m_up (up), m_back (back), m_translation (translation)
{

}

Vector4
Matrix4::getRight () const
{
    return m_right;
}

Vector4
Matrix4::getBack () const
{
    return m_back;
}

Vector4
Matrix4::getUp () const
{
    return m_up;
}

Vector4
Matrix4::getTranslation () const
{
    return m_translation;
}

void
Matrix4::setToIdentity ()
{
    *this = Matrix4 ();
}

void
Matrix4::setToZero ()
{
    m_right = Vector4 ();
    m_up = Vector4 ();
    m_back = Vector4 ();
    m_translation = Vector4 ();
}

const float*
Matrix4::data () const
{
    return &m_right.m_x;
}

void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
	double nearPlaneZ, double farPlaneZ)
{
    setToIdentity ();
    double fov = std::tan ((fovYDegrees * (M_PI / 180.f)) / 2.0f);
    
    m_right.m_x = 1.0f / (aspectRatio * fov);
    m_up.m_y = 1.0f / fov;

    m_back.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_back.m_w = -1.0f;

    m_translation.m_z = (2.0f * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_translation.m_w = 0.0f;
}

void
Matrix4::setToPerspectiveProjection (double left, double right,
	double bottom, double top,
	double nearPlaneZ, double farPlaneZ)
{
    setToIdentity ();

    m_right.m_x = ((2.0f * nearPlaneZ) / (right - left));
    m_up.m_y = ((2.0f * nearPlaneZ) / (top - bottom));

    m_back.m_x = (right + left) / (right - left);
    m_back.m_y = (top + bottom) / (top - bottom);
    m_back.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_back.m_w = -1.0f;

    m_translation.m_z = (2.0f * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ);
    m_translation.m_w = 0.0f;
}

void
Matrix4::setToOrthographicProjection (double left, double right,
    double bottom, double top,
    double nearPlaneZ, double farPlaneZ)
{
    setToIdentity();

    m_right.m_x = (2.0f / (right - left));
    m_up.m_y = (2.0f / (top - bottom));
    m_back.m_z = (2.0f / (nearPlaneZ - farPlaneZ));

    m_translation.m_x = -((right + left) / (right - left));
    m_translation.m_y = -((top + bottom) / (top - bottom));
    m_translation.m_z = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
}

std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
    out << std::setprecision(2) << std::fixed
        << Vector4 (m.getRight ().m_x, m.getUp ().m_x, m.getBack ().m_x, m.getTranslation ().m_x) << std::setw(10) << std::endl
		<< Vector4 (m.getRight ().m_y, m.getUp ().m_y, m.getBack ().m_y, m.getTranslation ().m_y) << std::setw(10) << std::endl
		<< Vector4 (m.getRight ().m_z, m.getUp ().m_z, m.getBack ().m_z, m.getTranslation ().m_z) << std::setw(10) << std::endl
		<< Vector4 (m.getRight ().m_w, m.getUp ().m_w, m.getBack ().m_w, m.getTranslation ().m_w) << std::setw(10) << std::endl;

	return out;
}

bool
operator== (const Matrix4& m1, const Matrix4& m2)
{
    return m1.getRight () == m2.getRight () && m1.getUp () == m2.getUp () && m1.getBack () == m2.getBack () && m1.getTranslation () == m2.getTranslation ();
}