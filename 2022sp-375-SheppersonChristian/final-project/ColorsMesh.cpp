/// \file ColorsMesh.cpp
/// \brief Definition of ColorsMesh class and any associated global functions.
/// \author Ryan Ganzke
/// \version A08

#include "Mesh.hpp"
#include "ColorsMesh.hpp"

ColorsMesh::ColorsMesh (OpenGLContext* context, ShaderProgram* shader)
  : Mesh (context, shader)
{

}

unsigned int
ColorsMesh::getFloatsPerVertex () const
{
    return 3 * Mesh::getFloatsPerVertex ();
}

void
ColorsMesh::enableAttributes ()
{
    Mesh::enableAttributes ();
    
    const GLint COLOR_ATTRIB_INDEX = 1;
    
    m_context->enableVertexAttribArray (COLOR_ATTRIB_INDEX);
    m_context->vertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE,
            (6 * sizeof(float)), reinterpret_cast<void*> (3 * sizeof(float)));
    m_context->bindVertexArray (0);
}