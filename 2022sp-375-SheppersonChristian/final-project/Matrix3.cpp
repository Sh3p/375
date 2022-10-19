/// \file Matrix3.hpp
/// \brief Definition of Matrix3 class and any associated global functions.
/// \author Ryan Ganzke
/// \version A05

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Matrix3.hpp"

#define M_PI atan(1) * 4

float
det2 (float a, float b, float c, float d)
{
    return (a * d) - (b * c);
}

Matrix3::Matrix3 ()
{
    *this = Matrix3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
}

Matrix3::Matrix3 (float rx, float ry, float rz,
    float ux, float uy, float uz,
    float bx, float by, float bz)
    : m_right (rx, ry, rz), m_up (ux, uy, uz), m_back (bx, by, bz)
{
}

Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
    const Vector3& back)
    : m_right (right), m_up (up), m_back (back)
{
}

Matrix3::Matrix3 (const Vector3& up, const Vector3& back,
    bool makeOrthonormal)
    : m_right (m_up.cross (m_back)), m_up (up), m_back (back)
{
    if (makeOrthonormal)
    {
        orthonormalize ();
    }
}

Matrix3::~Matrix3 ()
{

}

void
Matrix3::setToIdentity ()
{
    *this = Matrix3();
}

void
Matrix3::setToZero ()
{
    *this = Matrix3(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
}

float*
Matrix3::data ()
{
    return &(m_right.m_x);
}

const float*
Matrix3::data () const 
{
    return &(m_right.m_x);
}

void
Matrix3::setRight (const Vector3& right)
{
    m_right = right;
}

Vector3
Matrix3::getRight () const 
{
    return m_right;
}

void
Matrix3::setUp (const Vector3& up)
{
    m_up = up;
}

Vector3
Matrix3::getUp () const
{
    return m_up;
}

void
Matrix3::setBack (const Vector3& back)
{
    m_back = back;
}

Vector3
Matrix3::getBack () const
{
    return m_back;
}

void
Matrix3::setForward (const Vector3& forward)
{
    m_back = -forward;
}

Vector3
Matrix3::getForward () const
{
    return -m_back;
}

void
Matrix3::invertRotation ()
{
    transpose ();
}

void
Matrix3::invert ()
{
    float det = determinant ();

    //Create adjugate matrix
    Vector3 right = Vector3 (det2 (m_up.m_y, m_back.m_y, m_up.m_z, m_back.m_z),
        -det2 (m_right.m_y, m_back.m_y, m_right.m_z, m_back.m_z),
        det2 (m_right.m_y, m_up.m_y, m_right.m_z, m_up.m_z)); 
    Vector3 up = Vector3 (-det2 (m_up.m_x, m_back.m_x, m_up.m_z, m_back.m_z),
        det2 (m_right.m_x, m_back.m_x, m_right.m_z, m_back.m_z),
        -det2 (m_right.m_x, m_up.m_x, m_right.m_z, m_up.m_z));
    Vector3 back = Vector3 (det2 (m_up.m_x, m_back.m_x, m_up.m_y, m_back.m_y),
        -det2 (m_right.m_x, m_back.m_x, m_right.m_y, m_back.m_y),
        det2 (m_right.m_x, m_up.m_x, m_right.m_y, m_up.m_y));
    
    
    *this = det * Matrix3 (right, up, back);
}

float
Matrix3::determinant () const
{
    float right = m_right.m_x * det2 (m_up.m_y, m_back.m_y, m_up.m_z, m_back.m_z);
    float up = m_up.m_x * det2 (m_right.m_y, m_back.m_y, m_right.m_z, m_back.m_z);
    float back = m_back.m_x * det2 (m_right.m_y, m_up.m_y, m_right.m_z, m_up.m_z);
    return right - up + back;
}

void
Matrix3::transpose ()
{
    Vector3 right = Vector3 (m_right.m_x, m_up.m_x, m_back.m_x);
    Vector3 up = Vector3 (m_right.m_y, m_up.m_y, m_back.m_y);
    Vector3 back = Vector3 (m_right.m_z, m_up.m_z, m_back.m_z);
    *this = Matrix3 (right, up, back);
}

void
Matrix3::orthonormalize ()
{
    m_back.normalize();

    m_right = m_up.cross(m_back);
    m_right.normalize();

    m_up = m_back.cross(m_right);
    m_up.normalize();
}

void
Matrix3::setToScale (float scale)
{
    setToIdentity();
    *this *= scale;
}

void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ)
{
    setToIdentity();
    m_right.m_x *= scaleX;
    m_up.m_y *= scaleY;
    m_back.m_z *= scaleZ; 
}

void
Matrix3::setToShearXByYz (float shearY, float shearZ)
{
    setToIdentity ();
    m_up.m_x = shearY;
    m_back.m_x = shearZ; 
}

void
Matrix3::setToShearYByXz (float shearX, float shearZ)
{
    setToIdentity ();
    m_right.m_y = shearX;
    m_back.m_y = shearZ; 
}

void
Matrix3::setToShearZByXy (float shearX, float shearY)
{
    setToIdentity ();
    m_right.m_z = shearX;
    m_up.m_z = shearY;
}

void
Matrix3::setToRotationX (float angleDegrees)
{
    setFromAngleAxis(angleDegrees, Vector3 (1, 0, 0));
}

void
Matrix3::setToRotationY (float angleDegrees)
{
    setFromAngleAxis(angleDegrees, Vector3 (0, 1, 0));
}

void
Matrix3::setToRotationZ (float angleDegrees)
{
    setFromAngleAxis(angleDegrees, Vector3 (0, 0, 1));
}

void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis)
{
    setToIdentity ();

    Vector3 normAxis = axis;
    normAxis.normalize ();

    float angleRadians = angleDegrees * (M_PI / 180.f);

    m_right.m_x = cos (angleRadians) + pow (normAxis.m_x, 2) * (1 - cos (angleRadians));
    m_up.m_x = normAxis.m_x * normAxis.m_y * (1 - cos (angleRadians)) - normAxis.m_z * sin (angleRadians);
    m_back.m_x = normAxis.m_x * normAxis.m_z * (1 - cos (angleRadians)) + normAxis.m_y * sin (angleRadians);
    m_right.m_y = normAxis.m_y * normAxis.m_x * (1 - cos (angleRadians)) + normAxis.m_z * sin (angleRadians);
    m_up.m_y = cos (angleRadians) + pow (normAxis.m_y, 2) * (1 - cos (angleRadians));
    m_back.m_y = normAxis.m_y * normAxis.m_z * (1 - cos (angleRadians)) - normAxis.m_x * sin (angleRadians);
    m_right.m_z = normAxis.m_z * normAxis.m_x * (1 - cos (angleRadians)) - normAxis.m_y * sin (angleRadians);
    m_up.m_z = normAxis.m_z * normAxis.m_y * (1 - cos (angleRadians)) + normAxis.m_x * sin (angleRadians);
    m_back.m_z = cos (angleRadians) + pow (normAxis.m_z, 2) * (1 - cos (angleRadians));

    orthonormalize();
}

void
Matrix3::negate ()
{
    *this *= -1.0;
}

Vector3
Matrix3::transform (const Vector3& v) const
{
    return *this * v;
}

Matrix3&
Matrix3::operator+= (const Matrix3& m)
{
    *this = Matrix3 (m_right + m.m_right, m_up + m.m_up, m_back + m.m_back);
    return *this;
}

Matrix3&
Matrix3::operator-= (const Matrix3& m)
{
    *this = Matrix3 (m_right - m.m_right, m_up - m.m_up, m_back - m.m_back);
    return *this;
}

Matrix3&
Matrix3::operator*= (float scalar)
{
    *this = Matrix3 (m_right * scalar, m_up * scalar, m_back * scalar);
    return *this;
}

Matrix3&
Matrix3::operator*= (const Matrix3& m)
{
    transpose ();

    Vector3 right = Vector3 (m_right.dot (m.getRight ()), m_up.dot (m.getRight ()), m_back.dot (m.getRight ()));
    Vector3 up = Vector3 (m_right.dot (m.getUp ()), m_up.dot (m.getUp ()), m_back.dot (m.getUp ()));
    Vector3 back = Vector3 (m_right.dot (m.getBack ()), m_up.dot (m.getBack ()), m_back.dot (m.getBack ()));
    *this =  Matrix3 (right, up, back);
    return *this;
}

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2)
{
    return (Matrix3) m1 += m2;
}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2)
{
    return (Matrix3) m1 -= m2;
}

Matrix3
operator- (const Matrix3& m)
{
    return (Matrix3) m * -1.0;
}

Matrix3
operator* (const Matrix3& m, float scalar)
{
    return (Matrix3) m *= scalar;
}

Matrix3
operator* (float scalar, const Matrix3& m)
{
    return (Matrix3) m *= scalar;
}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2)
{
    return (Matrix3) m1 *= m2;
}

Vector3
operator* (const Matrix3& m, const Vector3& v)
{
    Matrix3 mT = m;
    mT.transpose ();
    return Vector3 (mT.getRight ().dot (v), mT.getUp ().dot (v), mT.getBack ().dot (v));
}

std::ostream&
operator<< (std::ostream& out, const Matrix3& m)
{
    out << std::setprecision(2) << std::fixed
        << std::setw(10) << m.getRight () << std::endl
        << std::setw(10) << m.getUp () << std::endl
        << std::setw(10) << m.getBack () << std::endl;
    return out;
}

bool
operator== (const Matrix3& m1, const Matrix3& m2)
{
    return m1.getRight () == m2.getRight ()
        && m1.getUp () == m2.getUp ()
        && m1.getBack () == m2.getBack ();
}