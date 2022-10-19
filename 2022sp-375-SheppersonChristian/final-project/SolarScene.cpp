/// \file SolarScene.cpp
/// \brief Definition of SolarScene class and any associated global functions.
/// \author Ryan Ganzke
/// \version A02

#include "SolarScene.hpp"
#include "ColorsMesh.hpp"
#include "NormalsMesh.hpp"

SolarScene::SolarScene (OpenGLContext* context, ShaderProgram* colorInfo, ShaderProgram* normInfo, ShaderProgram* genInfo, Camera* camera)
  : Scene::Scene (genInfo, camera)
{
  // LIGHT SOURCES
  this->addPointLightSource (Vector3 (0.6f, 0.3f, 0.0f), Vector3 (0.9f, 0.8f, 0.5f), Vector3 (0.0f, 1.0f, 0.0f), Vector3 (0.9f, 0.9f, 0.9f));
  this->addDirectionalLightSource (Vector3 (0.6f, 0.3f, 0.0f), Vector3 (0.9f, 0.8f, 0.5f), Vector3 (1.0f, 0.0f, 0.0f));
  
  this->addSpotLightSource (Vector3 (1.0f, 1.0f, 1.0f), Vector3 (0.9f, 0.9f, 0.9f), Vector3 (0.4f, 0.4f, 1.0f), Vector3 (0.3f, 0.6f, 0.235f), Vector3 (0.0f, 0.0f, -1.0f), 0.5f, 0.5f);
  this->addSpotLightSource (Vector3 (0.0f, 0.0f, 1.0f), Vector3 (0.4f, 0.9f, 0.2f), Vector3 (6.0f, 3.0f, -2.0f), Vector3 (0.7f, 0.8f, 0.2f), Vector3 (-0.1f, -0.7f, 0.1f), 0.5f, 0.5f * 128);
  this->setUniforms ();

  // MATERIALS
  Material* emerald = new Material (Vector3 (0.0215f, 0.1745f, 0.00215f), Vector3 (0.07568f, 0.61424f, 0.07568f ),
    Vector3 (0.633f, 0.727811f, 0.633f), Vector3 (0.5f, 0.5f, 0.5f), 0.6f * 128.0f);
  Material* gold = new Material (Vector3 (0.24725f, 0.1995f, 0.0745f), Vector3 (0.75164f, 0.60648f, 0.22648f * 128.0f),
    Vector3 (0.628281f, 0.555802f, 0.366065f), Vector3 (0.5f, 0.5f, 0.5f), 0.4f * 128.0f);
  Material* redRubber = new Material (Vector3 (0.05f, 0.05f, 0.05f), Vector3 (0.5f, 0.4f, 0.4f), Vector3 (0.7f, 0.04f, 0.04f), Vector3 (0.5f, 0.5f, 0.5f), 0.078125f * 128.0f);
  Material* cyanPlas = new Material (Vector3 (0.0f, 0.1f, 0.06f), Vector3 (0.0f, 0.50980392f, 0.50980392f), Vector3 (0.50196078f, 0.50196078f, 0.50196078f), Vector3 (0.5f, 0.5f, 0.5f), 0.25f * 128.0f);
  Material* blackPlastic = new Material(Vector3(0.0, 0.0, 0.0), Vector3(0.01, 0.01, 0.01), Vector3(0.50, 0.50, 0.50), Vector3 (0.5f, 0.5f, 0.5f), 0.5f * 128.0f);
  Material* turqoise = new Material(Vector3(0.1f, 0.18725, 0.1745), Vector3(0.396, 0.74151, 0.69102), Vector3(0.297254, 0.30829, 0.306678), Vector3 (0.5f, 0.5f, 0.4f), 0.1f * 128.0f);
  // SUN MESH
  //NormalsMesh* sun = new NormalsMesh (context, genInfo, "models/sol.obj", 0, gold);

  // this->add ("sun", sun);
  // this->getMesh ("sun")->scaleWorld (0.03f);
  // this->getMesh ("sun")->moveUp (-20.0f);
  // this->getMesh("sun")->moveRight(30.0f);
  // this->getMesh ("sun")->prepareVao();

  
  NormalsMesh* mercury = new NormalsMesh (context, genInfo, "models/sol.obj", 0, gold);

  this->add ("mercury", mercury);
  this->getMesh ("mercury")->scaleWorld (0.02f);
  this->getMesh ("mercury")->moveRight (-230.0f);
  this->getMesh ("mercury")->scaleLocal (0.2f);
  this->getMesh ("mercury")->prepareVao();
  


   
  NormalsMesh* venus = new NormalsMesh (context, genInfo, "models/sol.obj", 0, emerald);

  this->add ("venus", venus);
  this->getMesh ("venus")->scaleWorld (0.02f);
  this->getMesh ("venus")->moveUp(200.0f);
  this->getMesh ("venus")->moveRight (-160.0f);
  this->getMesh ("venus")->scaleLocal (0.3f);
  this->getMesh ("venus")->prepareVao();

   NormalsMesh* earth = new NormalsMesh (context, genInfo, "models/sol.obj", 0, turqoise);

  this->add ("earth", earth);
  this->getMesh ("earth")->scaleWorld (0.03f);
  this->getMesh ("earth")->moveUp(200.0f);
  this->getMesh ("earth")->moveRight (-20.0f);
  this->getMesh ("earth")->scaleLocal (0.4f);
  this->getMesh ("earth")->prepareVao();

   NormalsMesh* mars = new NormalsMesh (context, genInfo, "models/sol.obj", 0, redRubber);

  this->add ("mars", mars);
  this->getMesh ("mars")->scaleWorld (0.03f);
  this->getMesh ("mars")->moveUp(200.0f);
  this->getMesh ("mars")->moveRight (85.0f);
  this->getMesh ("mars")->scaleLocal (0.4f);
  this->getMesh ("mars")->prepareVao();

   NormalsMesh* jupiter = new NormalsMesh (context, genInfo, "models/sol.obj", 0, gold);

  this->add ("jupiter", jupiter);
  this->getMesh ("jupiter")->scaleWorld (0.04f);
  this->getMesh ("jupiter")->moveUp(200.0f);
  this->getMesh ("jupiter")->moveRight (200.0f);
  this->getMesh ("jupiter")->scaleLocal (0.7f);
  this->getMesh ("jupiter")->prepareVao();
  
   NormalsMesh* asteroid1 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid1", asteroid1);
  this->getMesh ("asteroid1")->scaleWorld (0.02f);
  this->getMesh ("asteroid1")->moveUp(100.0f);
  this->getMesh ("asteroid1")->moveRight (230.0f);
  this->getMesh ("asteroid1")->scaleLocal (0.7f);
  this->getMesh ("asteroid1")->prepareVao();


NormalsMesh* asteroid2 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid2", asteroid2);
  this->getMesh ("asteroid2")->scaleWorld (0.02f);
  this->getMesh ("asteroid2")->moveRight (250.0f);
  this->getMesh ("asteroid2")->moveUp(370.0f);
  this->getMesh ("asteroid2")->scaleLocal (0.7f);
  this->getMesh ("asteroid2")->prepareVao();


NormalsMesh* asteroid3 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid3", asteroid3);
  this->getMesh ("asteroid3")->scaleWorld (0.02f);
  this->getMesh ("asteroid3")->moveRight (265.0f);
  this->getMesh ("asteroid3")->moveUp(300.0f);
  this->getMesh ("asteroid3")->scaleLocal (0.7f);
  this->getMesh ("asteroid3")->prepareVao();

  NormalsMesh* asteroid4 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid4", asteroid4);
  this->getMesh ("asteroid4")->scaleWorld (0.02f);
  this->getMesh ("asteroid4")->moveRight (70.0f);
  this->getMesh ("asteroid4")->moveUp(-30.0f);
  this->getMesh ("asteroid4")->scaleLocal (0.7f);
  this->getMesh ("asteroid4")->prepareVao();

  NormalsMesh* asteroid5 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid5", asteroid5);
  this->getMesh ("asteroid5")->scaleWorld (0.02f);
  this->getMesh ("asteroid5")->moveRight (270.0f);
  this->getMesh ("asteroid5")->moveUp(70.0f);
  this->getMesh ("asteroid5")->scaleLocal (0.7f);
  this->getMesh ("asteroid5")->prepareVao();

   NormalsMesh* asteroid6 = new NormalsMesh (context, genInfo, "models/asteroid.obj", 0, blackPlastic);

  this->add ("asteroid6", asteroid6);
  this->getMesh ("asteroid6")->scaleWorld (0.02f);
  this->getMesh ("asteroid6")->moveRight (270.0f);
  this->getMesh ("asteroid6")->moveUp(100.0f);
  this->getMesh ("asteroid6")->scaleLocal (0.7f);
  this->getMesh ("asteroid6")->prepareVao();


}

