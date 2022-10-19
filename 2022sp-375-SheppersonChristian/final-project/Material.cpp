/// \file Matrix3.hpp
/// \brief Definition of Material class and any associated global functions.
/// \author Ryan Ganzke & Christian Shepperson
/// \version A09

#include <assimp/types.h>
#include <assimp/material.h>

#include "Material.hpp"

Material::Material (Vector3 ambientReflection, Vector3 diffuseReflection,
    Vector3 specularReflection, Vector3 emissiveIntensity, float shininess)
  : m_ambient (ambientReflection), m_diffuse (diffuseReflection),
    m_specular (specularReflection), m_emissive (emissiveIntensity), m_shininess (shininess)
{

}

Material::~Material ()
{

}

void
Material::setUniforms (ShaderProgram* shader)
{
  shader->setUniformVector ("uAmbientReflection", m_ambient);
  shader->setUniformVector ("uDiffuseReflection", m_diffuse);
  shader->setUniformVector ("uSpecularReflection", m_specular);
  shader->setUniformFloat ("uSpecularPower", m_shininess);
  shader->setUniformVector ("uEmmissiveIntensity", m_emissive);
}