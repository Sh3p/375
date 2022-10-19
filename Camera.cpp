/// \file Mesh.cpp
/// \brief Definition of Camera class and any associated global functions.
/// \author Ryan Ganzke
/// \version A02

#include "Camera.hpp"

Camera::Camera (const Vector3& eyePosition, const Vector3& localBackDirection,
  float nearClipPlaneDistance, float farClipPlaneDistance,
  float aspectRatio, float verticalFieldOfViewDegrees)
  : m_world (Matrix3 (Vector3(0.0f, 1.0f, 0.0f), localBackDirection, true), eyePosition)
{
    setProjectionSymmetricPerspective (verticalFieldOfViewDegrees, aspectRatio, nearClipPlaneDistance, farClipPlaneDistance);
    getViewMatrix ();
    m_initWorld = m_world;
}

Camera::~Camera ()
{
    
}

void
Camera::setPosition (const Vector3& position)
{
    m_world.setPosition (position);
    getViewMatrix ();
}

void
Camera::moveRight (float distance)
{
    m_world.moveRight (distance);
    getViewMatrix ();
}
void
Camera::moveUp (float distance)
{
    m_world.moveUp (distance);
    getViewMatrix ();
}

void
Camera::moveBack (float distance)
{
    m_world.moveBack (distance);
    getViewMatrix ();
}

void
Camera::yaw (float degrees)
{
    m_world.yaw (degrees);
    getViewMatrix ();
}

void
Camera::pitch (float degrees)
{
    m_world.pitch (degrees);
    getViewMatrix ();
}

void
Camera::roll (float degrees)
{
    m_world.roll (degrees);
    getViewMatrix ();
}

Transform
Camera::getViewMatrix ()
{
    Transform m_rotInv;
    m_rotInv.setOrientation (m_world.getOrientation ());
    m_rotInv.invertRt ();

    Transform m_transInv;
    m_transInv.setPosition (-m_world.getPosition ());

    m_viewMatrix = m_rotInv * m_transInv;

    return m_viewMatrix;
}

void
Camera::setProjectionSymmetricPerspective (double verticalFovDegrees, double aspectRatio,
  double nearZ, double farZ)
{
    m_projectionMatrix.setToPerspectiveProjection (verticalFovDegrees, aspectRatio, nearZ, farZ);
}

void
Camera::setProjectionAsymmetricPerspective (double left, double right,
	double bottom, double top,
	double nearPlaneZ, double farPlaneZ)
{
    m_projectionMatrix.setToPerspectiveProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

void
Camera::setProjectionOrthographic (double left, double right,
    double bottom, double top,
    double nearPlaneZ, double farPlaneZ)
{
    m_projectionMatrix.setToOrthographicProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);
}

Matrix4
Camera::getProjectionMatrix ()
{
    return m_projectionMatrix;
}

Vector3
Camera::getEyePosition ()
{
    return m_world.getPosition ();
}

void
Camera::resetPose ()
{
    m_world = m_initWorld;
    getViewMatrix ();
}
