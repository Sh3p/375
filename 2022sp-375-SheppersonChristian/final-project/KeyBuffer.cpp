/// \file KeyBuffer.cpp
/// \brief Definition of KeyBuffer class and any associated global functions.
/// \author Ryan Ganzke
/// \version A04

#include "KeyBuffer.hpp"

KeyBuffer::KeyBuffer ()
{
    this->reset();
}

void
KeyBuffer::setKeyDown (int key)
{
    keyIsPressed[key] = true;
}

void
KeyBuffer::reset ()
{
    for (int key = 0; key < GLFW_KEY_LAST + 1; key++) {
        keyIsPressed[key] = false;
    }
}

void
KeyBuffer::setKeyUp (int key)
{
    keyIsPressed[key] = false;
}

bool
KeyBuffer::isKeyDown (int key) const
{
    return keyIsPressed[key];
}