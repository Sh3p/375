/// \file ColorsMesh.hpp
/// \brief Declaration of ColorsMesh class and any associated global functions.
/// \author Ryan Ganzke
/// \version A08

#include "Mesh.hpp"
#include "Material.hpp"

class ColorsMesh : public Mesh
{
public:
    ColorsMesh (OpenGLContext* context, ShaderProgram* shader);

    virtual unsigned int
    getFloatsPerVertex () const;
    
protected:
    virtual void
    enableAttributes ();
};