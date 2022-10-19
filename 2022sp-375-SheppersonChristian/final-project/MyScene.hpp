/// \file MyScene.hpp
/// \brief Declaration of MyScene class and any associated global functions.
/// \author Ryan GAznke
/// \version A02

#ifndef MYSCENE_HPP
#define MYSCENE_HPP

#include <vector>

#include "OpenGLContext.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "Geometry.hpp"

class MyScene : public Scene
{
public:
    MyScene (OpenGLContext* context, ShaderProgram* colorInfo, ShaderProgram* normInfo,
        ShaderProgram* genPhongInfo, Camera* camera);

    MyScene (const MyScene&) = delete;

    MyScene&
    operator= (const MyScene&) = delete;
};

#endif //MYSCENE.HPP