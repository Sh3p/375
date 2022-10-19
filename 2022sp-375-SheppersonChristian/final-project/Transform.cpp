/// \file Transform.cpp
/// \brief Definition of Transform class and any associated global functions.
/// \author Ryan Ganzke
/// \version A06

#include <iostream>
#include <iomanip>

#include "Transform.hpp"

Transform::Transform ()
{
	reset ();
}

Transform::Transform (const Matrix3& orientation, const Vector3& position)
{
	m_rotScale = orientation;
	m_position = position;
}

void
Transform::orthonormalize ()
{
	m_rotScale.orthonormalize ();
}

void
Transform::reset ()
{
	*this = Transform (Matrix3 (1, 0, 0, 0, 1, 0, 0, 0, 1), Vector3 (0, 0, 0));
}

Matrix4
Transform::getTransform () const
{
	Vector3 right = m_rotScale.getRight ();
	Vector3 up = m_rotScale.getUp ();
	Vector3 back = m_rotScale.getBack ();

	Vector4 g_right = Vector4 (right.m_x, right.m_y, right.m_z, 0);
	Vector4 g_up = Vector4 (up.m_x, up.m_y, up.m_z, 0);
	Vector4 g_back = Vector4 (back.m_x, back.m_y, back.m_z, 0);
	Vector4 g_pos = Vector4 (m_position.m_x, m_position.m_y, m_position.m_z, 1);

	return Matrix4 (g_right, g_up, g_back, g_pos);
}

void
Transform::getTransform (float array[16]) const
{
	const float *ptr = m_rotScale.data ();
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			array[(4 * i) + j] = *ptr;
			++ptr;
		}
		array[(4 * i) + 3] = 0.0f;
	}

	array[12] = m_position.m_x;
	array[13] = m_position.m_y;
	array[14] = m_position.m_z;
	array[15] = 1.0f;
}

Vector3
Transform::getPosition () const
{
	return m_position;
}

void
Transform::setPosition (const Vector3& position)
{
	m_position = position;
}

void
Transform::setPosition (float x, float y, float z)
{
	m_position = Vector3 (x, y, z);
}

Vector3
Transform::getRight () const
{
	return m_rotScale.getRight ();
}

Vector3
Transform::getUp () const
{
	return m_rotScale.getUp ();
}

Vector3
Transform::getBack () const
{
	return m_rotScale.getBack ();
}

Matrix3
Transform::getOrientation () const
{
	return m_rotScale;
}

void
Transform::setOrientation (const Matrix3& orientation)
{
	m_rotScale = orientation;
}

void
Transform::setOrientation (const Vector3& right, const Vector3& up,
		  const Vector3& back)
{
	m_rotScale = Matrix3 (right, up, back);
}

void
Transform::moveRight (float distance)
{
	moveLocal(distance, m_rotScale.getRight ());
}
void
Transform::moveUp (float distance)
{
	moveLocal(distance, m_rotScale.getUp ());
}
void
Transform::moveBack (float distance)
{
	moveLocal(distance, m_rotScale.getBack ());
}

void
Transform::moveLocal (float distance, const Vector3& localDirection)
{
	m_position += distance * localDirection;
}

void
Transform::moveWorld (float distance, const Vector3& worldDirection)
{
	m_position += m_rotScale * (distance * worldDirection);
}

void
Transform::pitch (float angleDegrees)
{
	Matrix3 rotation;
	rotation.setToRotationX(angleDegrees);
	m_rotScale *= rotation;
}

void
Transform::yaw (float angleDegrees)
{
	Matrix3 rotation;
	rotation.setToRotationY(angleDegrees);
	m_rotScale *= rotation;
}

void
Transform::roll (float angleDegrees)
{
    Matrix3 rotation;
	rotation.setToRotationZ(angleDegrees);
	m_rotScale *= rotation;
}

void
Transform::rotateLocal (float angleDegrees, const Vector3& axis)
{
	Matrix3 rotation;
	rotation.setFromAngleAxis(angleDegrees, axis);
	m_rotScale *= rotation;
}

void
Transform::alignWithWorldY ()
{
	Matrix3 m_yAlign;
	m_yAlign.setBack(m_yAlign.getRight ().cross (m_yAlign.getUp ()));
	m_yAlign.getBack ().normalize ();

    m_yAlign.setRight (m_yAlign.getUp ().cross (m_yAlign.getBack ()));
    m_yAlign.getRight ().normalize ();

	m_rotScale = m_yAlign;
}

void
Transform::rotateWorld (float angleDegrees, const Vector3& axis)
{
	Matrix3 rotation;
	rotation.setFromAngleAxis(angleDegrees, axis);
	m_rotScale = rotation * m_rotScale;
	m_position = rotation * m_position;
}

void
Transform::scaleLocal (float scale)
{
	m_rotScale *= scale;
}

void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
	Matrix3 m_scale;
	m_scale.setToScale (scaleX, scaleY, scaleZ);
	m_rotScale *= m_scale;
}

void
Transform::scaleWorld (float scale)
{
	Matrix3 m_scale;
	m_scale.setToScale (scale);
	m_rotScale = m_rotScale * m_scale;

	m_position *= scale;
}

void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
	Matrix3 m_scale;
	m_scale.setToScale (scaleX, scaleY, scaleZ);
	m_rotScale = m_scale * m_rotScale;

	m_position.set (m_position.m_x * scaleX, m_position.m_y * scaleY, m_position.m_z * scaleZ);
}

void
Transform::shearLocalXByYz (float shearY, float shearZ)
{
	Matrix3 m_shear;
	m_shear.setToShearXByYz (shearY, shearZ);
	m_rotScale *= m_shear;
}

void
Transform::shearLocalYByXz (float shearX, float shearZ)
{
	Matrix3 m_shear;
	m_shear.setToShearYByXz (shearX, shearZ);
	m_rotScale *= m_shear;
}

void
Transform::shearLocalZByXy (float shearX, float shearY)
{
	Matrix3 m_shear;
	m_shear.setToShearZByXy (shearX, shearY);
	m_rotScale *= m_shear;
}

void
Transform::invertRt ()
{
	Vector3 m_invertPos = Vector3 (-m_position.m_x, -m_position.m_y, -m_position.m_z);
	m_position.m_x =  m_rotScale.getRight ().dot (m_invertPos);
	m_position.m_y = m_rotScale.getUp ().dot (m_invertPos);
	m_position.m_z = m_rotScale.getBack ().dot (m_invertPos);
	m_rotScale.invertRotation ();
}

void
Transform::combine (const Transform& t)
{
	*this = *this * t;
}

Transform
operator* (const Transform& t1, const Transform& t2)
{
	Transform result;
	result.setOrientation (t1.getOrientation () * t2.getOrientation ());
	result.setPosition (t1.getOrientation () * t2.getPosition () + t1.getPosition ());
	return result;
}

std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
	Matrix3 m_temp = t.getOrientation ();
	m_temp.transpose ();

	out << std::setprecision(2) << std::fixed
        << m_temp.getRight () << std::setw(10) << t.getPosition ().m_x << std::endl
		<< m_temp.getUp () << std::setw(10) << t.getPosition ().m_y << std::endl
		<< m_temp.getBack () << std::setw(10) << t.getPosition ().m_z << std::endl
		<< std::setw(10) << 0.0f
		<< std::setw(10) << 0.0f
		<< std::setw(10) << 0.0f
		<< std::setw(10) << 1.0f << std::endl;

	return out;
}

bool
operator== (const Transform& t1, const Transform& t2)
{
    return t1.getOrientation () == t2.getOrientation () && t1.getPosition () == t2.getPosition ();
}