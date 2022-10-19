/// \file Scene.cpp
/// \brief Definition of Scene class and any associated global functions.
/// \author Ryan Ganzke
/// \version A02

#include "Scene.hpp"

Scene::Scene (ShaderProgram* shader, Camera* camera)
  : s_meshes (), s_activeMesh (s_meshes.begin ()), s_shader (shader), s_camera (camera)
{

}

Scene::~Scene ()
{
  clear();
}

void
Scene::add (const std::string& meshName, Mesh* mesh)
{
  s_meshes[meshName] = mesh;

  if(s_meshes.size () == 1)
    s_activeMesh = s_meshes.begin();
}

void
Scene::remove (const std::string& meshName)
{
  if (s_activeMesh->second == s_meshes[meshName])
    activateNextMesh ();
  delete s_meshes[meshName];
  s_meshes.erase(meshName);
}

void
Scene::clear () {
  for (auto& mesh : s_meshes)
    delete mesh.second;
  s_meshes.clear();
}

void
Scene::draw (const Transform &viewMatrix, const Matrix4& projectionMatrix)
{
  setUniforms ();
  for (auto& mesh : s_meshes)
    mesh.second->draw(viewMatrix, projectionMatrix);
}

bool
Scene::hasMesh (const std::string& meshName)
{
  return s_meshes.find (meshName) != s_meshes.end ();
}

Mesh*
Scene::getMesh (const std::string& meshName)
{
  return s_meshes.at (meshName);
}

void
Scene::setActiveMesh (const std::string& meshName)
{
  s_activeMesh = s_meshes.find (meshName);
}

Mesh*
Scene::getActiveMesh ()
{
  return s_activeMesh->second;
}

void
Scene::activateNextMesh ()
{
  ++s_activeMesh;
  if (s_activeMesh == s_meshes.end ())
    s_activeMesh = s_meshes.begin ();
}

void
Scene::activatePreviousMesh ()
{
  if (s_activeMesh == s_meshes.begin ())
    s_activeMesh = s_meshes.end ();
  --s_activeMesh;
}

void
Scene::addDirectionalLightSource (const Vector3& diffuseIntensity,
    const Vector3& specularIntensity, const Vector3& direction)
{
  s_lightSource.emplace_back (new DirectionalLightSource (diffuseIntensity, specularIntensity,
    direction));
}

void
Scene::addPointLightSource (const Vector3& diffuseIntensity,
    const Vector3& specularIntensity, const Vector3& position, const Vector3& attenuationCoefficients)
{
  s_lightSource.emplace_back (new PointLightSource (diffuseIntensity, specularIntensity, position,
    attenuationCoefficients));
}

void
Scene::addSpotLightSource (const Vector3& diffuseIntensity, const Vector3& specularIntensity,
    const Vector3& position, const Vector3& attenuationCoefficients, const Vector3& direction,
    float cutoffCosAngle, float falloff)
{
  s_lightSource.emplace_back (new SpotLightSource (diffuseIntensity, specularIntensity, position,
    attenuationCoefficients, direction, cutoffCosAngle, falloff));
}

void
Scene::setUniforms ()
{
  s_shader->enable ();
  s_shader->setUniformVector ("uEyePosition", s_camera->getEyePosition ());
  s_shader->setUniformInt ("uNumLights", s_lightSource.size());
  for (int i = 0; i < s_lightSource.size(); i++)
  {
    s_lightSource[i]->setUniforms (s_shader, i);
  }
}