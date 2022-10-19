#version 330

/*
  Filename: GeneralShader.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A09Project
  Description: A vertex shader that demonstrates how up to 8 light sources of a
    variety of types could be provided.
*/

// By default, all float variables will use high precision.
precision highp float;

// Single ambient light, provided by the C++ code.
uniform vec3  uAmbientIntensity;

// Material properties, provided by the C++ code.
uniform vec3  uAmbientReflection;
uniform vec3  uEmissiveIntensity;

// Inputs from the VBO.
in vec3 aPosition;
layout (location = 2) in vec3 aNormal;

// Output to the fragment shader.
out vec3 vColor;
out vec3 vPosition;
out vec3 vNormal;

// Transformation matrices, provided by C++ code.
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uWorld;

// Eye posiiton, in world space, provided by C++ code.
uniform vec3 uEyePosition;

// **

void
main (void)
{
  mat4 worldViewProjection = uProjection * uView * uWorld;
  // Transform vertex into clip space
  gl_Position = worldViewProjection * vec4 (aPosition, 1);
  // Transform vertex into world space for lighting
  vec3 positionEye = vec3 (uView * uWorld * vec4 (aPosition, 1));

  // We're doing lighting in world space for this example!
  mat3 normalTransform = mat3 (uView * uWorld);
  normalTransform = transpose (inverse (normalTransform));
  // Normal matrix is world inverse transpose
  vec3 normalEye = normalize (normalTransform * aNormal);

  // Handle ambient and emissive light
  //   It's independent of any particular light
  vColor = uAmbientReflection * uAmbientIntensity
      + uEmissiveIntensity;

  // Stay in bounds [0, 1]
  vColor = clamp (vColor, 0.0, 1.0);

  vPosition = positionEye;
  vNormal = normalEye;
}
