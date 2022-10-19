/// \file MyScene.cpp
/// \brief Definition of MyScene class and any associated global functions.
/// \author Ryan Ganzke
/// \version A02

#include "MyScene.hpp"
#include "ColorsMesh.hpp"
#include "NormalsMesh.hpp"

MyScene::MyScene (OpenGLContext* context, ShaderProgram* colorInfo, ShaderProgram* normInfo,
  ShaderProgram* genPhongInfo, Camera* camera)
  : Scene::Scene (genPhongInfo, camera)
{
  // 3 3D points, followed by 3 RGB colors
  std::vector<float> decaVertices {
    // FRONT SIDE OF DECAGON
    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    -3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 
    3.0f, -3.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 
    
    3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 
    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f,

    // LEFT SIDE OF DECAGON
    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    -3.0f, -3.0f, -6.0f,
    0.0f, 0.0f, 0.0f, 
    -3.0f, -3.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 

    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    -3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,  
    -3.0f, -3.0f, -6.0f,
    0.0f, 0.0f, 0.0f, 

    // BACK SIDE OF DECAGON
    -3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f, 
    -3.0f, -3.0f, -6.0f, 
    0.0f, 0.0f, 0.0f,

    -3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f, 
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f,

    // RIGHT SIDE OF DECAGON
    3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f,

    3.0f, 3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f,

    //TOP SPIKE OF DECAGON
    0.0f, 5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 
    3.0f, 3.0f, 0.0f, 
    0.0f, 0.0f, 0.0f,

    0.0f, 5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, 3.0f, 0.0f,
    1.0f, 1.0f, 1.0f,

    0.0f, 5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, 3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, 5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, 3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,

    // BOTTOM SPIKE OF DECAGON
    0.0f, -5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, -5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, -3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,

    0.0f, -5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    -3.0f, -3.0f, -6.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f,

    0.0f, -5.0f, -3.0f,
    0.0f, 0.0f, 0.0f,
    3.0f, -3.0f, -6.0f,
    1.0f, 1.0f, 1.0f,
    3.0f, -3.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
  };

  std::vector<float> triVertices {
    -11.0f, 9.0f, -10.0f,
    0.0f, 0.0f, 0.3f,
    -6.0f, 2.0f, -3.0f,
    0.0f, 0.0f, 0.3f,
    -4.0f, 8.0f, -7.0f, 
    0.0f, 0.0f, 0.3f,

    -11.0f, 9.0f, -10.0f,
    0.3f, 0.0f, 0.0f,
    -4.0f, 8.0f, -7.0f, 
    0.3f, 0.0f, 0.0f,
    -6.0f, 2.0f, -3.0f,
    0.3f, 0.0f, 0.0f,
  };

  // LIGHT SOURCES
  this->addDirectionalLightSource (Vector3 (0.6f, 0.3f, 0.0f), Vector3 (0.9f, 0.8f, 0.5f), Vector3 (-1.0f, 0.0f, 0.0f));
  this->addSpotLightSource (Vector3 (0.0f, 1.0f, 0.0f), Vector3 (0.2f, 0.2f, 0.2f), Vector3 (-1.0f, 0.0f, 0.0f), Vector3 (0.9f, 0.9f, 0.9f), Vector3 (0.5f, 0.5f, 0.5f), 0.5f, 0.5f);
  this->addSpotLightSource (Vector3 (0.0f, 0.0f, 1.0f), Vector3 (0.4f, 0.9f, 0.2f), Vector3 (6.0f, 3.0f, -2.0f), Vector3 (0.7f, 0.8f, 0.2f), Vector3 (-0.1f, -0.7f, 0.1f), 0.5f, 0.5f);
  this->setUniforms ();

  // MATERIALS
  Material* emerald = new Material (Vector3 (0.0215f, 0.1745f, 0.00215f), Vector3 (0.07568f, 0.61424f, 0.07568f),
    Vector3 (0.633f, 0.727811f, 0.633f), Vector3 (0.5f, 0.5f, 0.5f), 0.6f);

  Material* gold = new Material (Vector3 (0.24725f, 0.1995f, 0.0745f), Vector3 (0.75164f, 0.60648f, 0.22648f),
    Vector3 (0.628281f, 0.555802f, 0.366065f), Vector3 (0.5f, 0.5f, 0.5f), 0.4f);

  Material* redRubber = new Material (Vector3 (0.05f, 0.05f, 0.05f), Vector3 (0.5f, 0.4f, 0.4f), Vector3 (0.7f, 0.04f, 0.04f), Vector3 (0.5f, 0.5f, 0.5f), 0.078125f);

  // DECAGON MESH

  // std::vector<float> decaData;
  // std::vector<unsigned int> decaIndices;

  // indexData (decaVertices, 6, decaData, decaIndices);

  // this->add ("decagon", new ColorsMesh (context, colorInfo, emerald));
  // this->getMesh ("decagon")->addGeometry(decaData);
  // this->getMesh ("decagon")->addIndices(decaIndices);
  // this->getMesh ("decagon")->prepareVao();

  // TRIANGLE MESH

  // std::vector<float> triData;
  // std::vector<unsigned int> triIndices;

  // indexData (triVertices, 6, triData, triIndices);

  // this->add ("triangle", new ColorsMesh (context, colorInfo, emerald));
  // this->getMesh ("triangle")->addGeometry(triData);
  // this->getMesh ("triangle")->addIndices(triIndices);
  // this->getMesh ("triangle")->prepareVao();

  // std::vector<Triangle> cubeBase = buildCube ();

  // FIRST CUBE

  // std::vector<float> firstCubeData;
  // std::vector<unsigned int> firstCubeIndices;

  // ColorsMesh* firstCube = new ColorsMesh (context, colorInfo, emerald);
  // std::vector<Vector3> firstCubeFaceColors = generateRandomFaceColors (cubeBase);
  // std::vector<float> firstCubeVertices = dataWithFaceColors (cubeBase, firstCubeFaceColors);
  // indexData (firstCubeVertices, firstCube->getFloatsPerVertex (), firstCubeData, firstCubeIndices);

  // this->add ("first cube", firstCube);
  // this->getMesh ("first cube")->addGeometry (firstCubeData);
  // this->getMesh ("first cube")->addIndices (firstCubeIndices);
  // this->getMesh ("first cube")->moveRight (-6.0f);
  // this->getMesh ("first cube")->moveUp (4.5f);
  // this->getMesh ("first cube")->prepareVao ();

  // SECOND CUBE

  // std::vector<float> secondCubeData;
  // std::vector<unsigned int> secondCubeIndices;

  // ColorsMesh* secondCube = new ColorsMesh (context, colorInfo, emerald);
  // std::vector<Vector3> secondCubeVertColors = generateRandomVertexColors (cubeBase);
  // std::vector<float> secondCubeVertices = dataWithVertexColors (cubeBase, secondCubeVertColors);
  // indexData (secondCubeVertices, secondCube->getFloatsPerVertex (), secondCubeData, secondCubeIndices);

  // this->add ("second cube", secondCube);
  // this->getMesh ("second cube")->addGeometry(secondCubeData);
  // this->getMesh ("second cube")->addIndices(secondCubeIndices);
  // this->getMesh ("second cube")->moveRight (-6.0f);
  // this->getMesh ("second cube")->moveUp (1.5f);
  // this->getMesh ("second cube")->prepareVao();

  // THIRD CUBE

  // std::vector<float> thirdCubeData;
  // std::vector<unsigned int> thirdCubeIndices;

  // NormalsMesh* thirdCube = new NormalsMesh (context, normInfo, emerald);
  // std::vector<Vector3> faceNormals = computeFaceNormals (cubeBase);
  // std::vector<float> thirdCubeVertices = dataWithFaceNormals (cubeBase, faceNormals);
  // indexData (thirdCubeVertices, thirdCube->getFloatsPerVertex (), thirdCubeData, thirdCubeIndices);

  // this->add ("third cube", thirdCube);
  // this->getMesh ("third cube")->addGeometry(thirdCubeData);
  // this->getMesh ("third cube")->addIndices(thirdCubeIndices);
  // this->getMesh ("third cube")->moveRight (-6.0f);
  // this->getMesh ("third cube")->moveUp (-1.5f);
  // this->getMesh ("third cube")->prepareVao();

  // FOURTH CUBE

  // std::vector<float> fourthCubeData;
  // std::vector<unsigned int> fourthCubeIndices;

  // NormalsMesh* fourthCube = new NormalsMesh (context, normInfo, emerald);
  // std::vector<Vector3> vertexNormals = computeVertexNormals (cubeBase, faceNormals);
  // std::vector<float> fourthCubeVertices = dataWithVertexNormals (cubeBase, vertexNormals);
  // indexData (fourthCubeVertices, fourthCube->getFloatsPerVertex (), fourthCubeData, fourthCubeIndices);

  // this->add ("fourth cube", fourthCube);
  // this->getMesh ("fourth cube")->addGeometry(fourthCubeData);
  // this->getMesh ("fourth cube")->addIndices(fourthCubeIndices);
  // this->getMesh ("fourth cube")->moveRight (-6.0f);
  // this->getMesh ("fourth cube")->moveUp (-4.5f);
  // this->getMesh ("fourth cube")->prepareVao();

  // BEAR1 MESH
  NormalsMesh* bear1 = new NormalsMesh (context, genPhongInfo, "models/bear.obj", 0, emerald);

  this->add ("bear1", bear1);
  this->getMesh ("bear1")->scaleWorld (0.25f);
  this->getMesh ("bear1")->moveRight (10.0f);
  this->getMesh ("bear1")->moveUp (-3.0f);
  this->getMesh ("bear1")->yaw (-40.0f);
  this->getMesh ("bear1")->prepareVao();

  // BEAR2 MESH

  NormalsMesh* bear2 = new NormalsMesh (context, genPhongInfo, "models/bear.obj", 0, gold);

  this->add ("bear2", bear2);
  this->getMesh ("bear2")->scaleWorld (0.25f);
  this->getMesh ("bear2")->moveRight (-10.0f);
  this->getMesh ("bear2")->moveUp (-3.0f);
  this->getMesh ("bear2")->yaw (40.0f);
  this->getMesh ("bear2")->prepareVao();

  // BEAR3 MESH

  NormalsMesh* bear3 = new NormalsMesh (context, genPhongInfo, "models/bear.obj", 0, redRubber);

  this->add ("bear3", bear3);
  this->getMesh ("bear3")->scaleWorld (0.25f);
  this->getMesh ("bear3")->moveUp (6.0f);
  this->getMesh ("bear3")->scaleLocal (0.60f);
  this->getMesh ("bear3")->prepareVao();
}