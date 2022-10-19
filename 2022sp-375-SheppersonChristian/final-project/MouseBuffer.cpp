/// \file MouseBuffer.cpp
/// \brief Definition of MouseBuffer class and any associated global functions.
/// \author Ryan Ganzke
/// \version A06

#include "MouseBuffer.hpp"

MouseBuffer::MouseBuffer ()
: m_leftButton (false), m_rightButton (false), m_xPos (0), m_yPos (0)
{

}

void
MouseBuffer::setLeftButton (bool down)
{
    m_leftButton = down;
}

void
MouseBuffer::setRightButton (bool down)
{
    m_rightButton = down;
}

bool
MouseBuffer::getLeftButton () const
{
    return m_leftButton;
}

bool
MouseBuffer::getRightButton () const
{
    return m_rightButton;
}

void
MouseBuffer::setPosition (double x, double y)
{
    m_xPos = x;
    m_yPos = y;
}

double
MouseBuffer::getX () const
{
    return m_xPos;
}

double
MouseBuffer::getY () const
{
    return m_yPos;
}