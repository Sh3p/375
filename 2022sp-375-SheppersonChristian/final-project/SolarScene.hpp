/// \file MyScene.hpp
/// \brief Declaration of MyScene class and any associated global functions.
/// \author Ryan GAznke
/// \version A02

#ifndef SOLARSCENE_HPP
#define SOLARSCENE_HPP

#include <vector>

#include "OpenGLContext.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "MyScene.hpp"
#include "Geometry.hpp"

class SolarScene : public Scene
{
public:
    SolarScene (OpenGLContext* context, ShaderProgram* colorInfo, ShaderProgram* normInfo, ShaderProgram* genInfo, Camera* camera);

    SolarScene (const SolarScene&) = delete;

    SolarScene&
    operator= (const SolarScene&) = delete;
};

#endif //MYSCENE.HPP