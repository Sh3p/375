/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg
/// \version A02
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.  It
///   allows limited movement of a very simple virtual camera.


/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>

/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "MyScene.hpp"
#include "SolarScene.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "KeyBuffer.hpp"
#include "Transform.hpp"
#include "MouseBuffer.hpp"

/******************************************************************/
// Local types

/// \brief The location and orientation through which we view the Scene.
///
/// This will be replaced in a future assignment with a much more robust and
///   interesting version, but is sufficient for now.
// struct Camera
// {
//   /// The location of this Camera in world coordinates.
//   glm::vec3 position;
//   /// The point in world coordinates that this Camera is focusing on.
//   glm::vec3 at;
//   /// The direction in world coordinates that this Camera considers to be up.
//   glm::vec3 up;
//   /// A projection matrix for this Camera.
//   glm::mat4 projection;
// };

/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

// We use one VAO for each object we draw
/// \brief A collection of the VAOs for each of the objects we want to draw.
///
/// This will be filled in initScene, and its contents need to be deleted in
///   releaseGlResources.


SolarScene* g_scene; //scene used for project

//MyScene* g_scene; use for default my scene

/// \brief The ShaderProgram that transforms and lights the primitives.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderColorProgram;

ShaderProgram* g_shaderNormProgram;

ShaderProgram* g_shaderGenProgram;

ShaderProgram* g_shaderPhongProgram;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

/// \brief The KeyBuffer that controls keyboard input.
///
KeyBuffer g_keyBuffer;

/// \brief The MouseBuffer that controls keyboard input.
///
MouseBuffer g_mouseBuffer;

// Define the projection, which will remain constant
float g_verticalFov = 50.0f;
float aspectRatio = 1200.0f / 900;
// Near plane
float nearZ = 0.01f;
// Far plane
float farZ = 40.0f;

/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init (GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw ();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew ();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow (GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to reset.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport (GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene ();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders ();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera ();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene (double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene (GLFWwindow* window);

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

void
processKeys ();

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The button that was pressed or released.
/// \param[in] action What happened to the button.
/// \param[in] modifiers Which modifier buttons were depressed.
void
recordMouse (GLFWwindow* window, int button, int action, int modifiers);

void
processMouse (GLFWwindow* window);

void processScroll (GLFWwindow* window, double xOff, double yOff);

/// \brief Cleans up all resources as program exits.
void
releaseGlResources ();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError (int error, const char* description);


void
SolarMove();

int g_resetSolar = 0;

/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main (int argc, char* argv[])
{
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
      // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    SolarMove();
    // processKeys ();
    // processMouse (window);
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  g_context = new RealOpenGLContext ();
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (800, 600, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 300, 200);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys);
  glfwSetMouseButtonCallback (window, recordMouse);
  glfwSetScrollCallback (window, processScroll);
  glfwSetFramebufferSizeCallback (window, resetViewport);

  // Specify background color
  g_context->clearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace (GL_CCW);
  g_context->cullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  g_camera->setProjectionSymmetricPerspective (g_verticalFov, aspectRatio, nearZ, farZ);
  g_context->viewport (0, 0, width, height);
}

/******************************************************************/

void
initScene ()
{
  g_scene = new SolarScene (g_context, g_shaderColorProgram, g_shaderNormProgram, g_shaderPhongProgram, g_camera);
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderColorProgram = new ShaderProgram (g_context);
  g_shaderColorProgram->createVertexShader ("shaders/Vec3.vert");
  g_shaderColorProgram->createFragmentShader ("shaders/Vec3.frag");
  g_shaderColorProgram->link ();

  g_shaderNormProgram = new ShaderProgram (g_context);
  g_shaderNormProgram->createVertexShader ("shaders/Vec3Norm.vert");
  g_shaderNormProgram->createFragmentShader ("shaders/Vec3.frag");
  g_shaderNormProgram->link ();

  g_shaderGenProgram = new ShaderProgram (g_context);
  g_shaderGenProgram->createVertexShader ("shaders/GeneralShader.vert");
  g_shaderGenProgram->createFragmentShader ("shaders/GeneralShader.frag");
  g_shaderGenProgram->link ();

  g_shaderPhongProgram = new ShaderProgram (g_context);
  g_shaderPhongProgram->createVertexShader ("shaders/PhongShader.vert");
  g_shaderPhongProgram->createFragmentShader ("shaders/PhongShader.frag");
  g_shaderPhongProgram->link ();
}

/******************************************************************/

void
initCamera ()
{
  g_camera = new Camera(Vector3 (0, 0, 12.0f), Vector3 (0, 0, 1), nearZ, farZ, aspectRatio, g_verticalFov);
}

/******************************************************************/

void
updateScene (double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  g_context->clear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  g_scene->draw(g_camera->getViewMatrix(), g_camera->getProjectionMatrix());

  glfwSwapBuffers (window);
}


/******************************************************************/

//movement for solar system
void
SolarMove(){
  g_camera->roll(0.01);
  g_camera->pitch(0.05);
  g_camera->yaw(0.04);
  
  g_camera->moveRight(0.01);
  g_scene->getMesh("earth")->yaw(0.80);
  g_scene->getMesh("earth")->roll(0.20);
  g_scene->getMesh("earth")->pitch(0.40);
  g_scene->getMesh("mars")->roll(1.0);
  g_scene->getMesh("mars")->moveUp(0.1);
  g_scene->getMesh("asteroid2")->roll(0.90);
  g_scene->getMesh("asteroid3")->roll(0.50);
  g_scene->getMesh("asteroid1")->roll(-0.50);
  g_scene->getMesh("asteroid4")->roll(-0.50);
  g_scene->getMesh("asteroid5")->roll(-0.50);
  g_scene->getMesh("asteroid5")->yaw(-0.50);
   g_scene->getMesh("asteroid6")->roll(-0.50);
  g_scene->getMesh("asteroid6")->yaw(-0.50);
  g_scene->getMesh("asteroid1")->moveRight(-0.2);
  g_scene->getMesh("asteroid2")->moveRight(-0.5);
  g_scene->getMesh("asteroid3")->moveRight(0.1);
  g_scene->getMesh("asteroid4")->moveRight(0.9);
  g_scene->getMesh("asteroid5")->moveRight(0.5);
  g_scene->getMesh("venus")->yaw(0.90);
  g_scene->getMesh("venus")->roll(0.90);
  g_scene->getMesh("jupiter")->roll(0.50);
  g_scene->getMesh("jupiter")->pitch(0.30);
  g_scene->getMesh("mercury")->yaw(0.50);
  g_scene->getMesh("mercury")->roll(0.80);
  g_scene->getMesh("mercury")->pitch(0.40);
  ++g_resetSolar;
  if(g_resetSolar == 1200){
    g_camera->resetPose();
    g_resetSolar = 0;
  }
}



void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }
  else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    g_scene->activatePreviousMesh ();
  else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    g_scene->activateNextMesh ();
  else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    g_camera->setProjectionSymmetricPerspective (g_verticalFov, aspectRatio, nearZ, farZ);
  else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
    g_camera->setProjectionAsymmetricPerspective (-4.0f, 6.0f, -6.0f, 5.0f, 2.0, 20.0);
  else if (key == GLFW_KEY_O && action == GLFW_PRESS)
    g_camera->setProjectionOrthographic (-4.0f, 6.0f, -6.0f, 5.0f, 2.0f, 30.0f);


  // Record keyboard input in regards to movement
  if (action == GLFW_PRESS)
    g_keyBuffer.setKeyDown(key);
  else if (action == GLFW_RELEASE)
    g_keyBuffer.setKeyUp(key);
}

void
processKeys ()
{
  // Translate camera/eye point using WASD keys
  const float MOVEMENT_DELTA = 0.1f;

  for (int key = 0; key < GLFW_KEY_LAST; ++key)
  {
    if (g_keyBuffer.isKeyDown (key))
    {
      if (key == GLFW_KEY_A)
        g_camera->moveRight(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_D)
        g_camera->moveRight(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_C)
        g_camera->moveUp(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_F)
        g_camera->moveUp(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_W)
        g_camera->moveBack(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_S)
        g_camera->moveBack(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_J)
        g_scene->getActiveMesh ()->yaw (MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_L)
        g_scene->getActiveMesh ()->yaw (-MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_R)
        g_camera->resetPose();
      else if (key == GLFW_KEY_I)
        g_scene->getActiveMesh ()->pitch (MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_K)
        g_scene->getActiveMesh ()->pitch (-MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_M)
        g_scene->getActiveMesh ()->roll (MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_N)
        g_scene->getActiveMesh ()->roll (-MOVEMENT_DELTA * 5);
      else if (key == GLFW_KEY_1)
        g_scene->getActiveMesh ()->moveRight (-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_2)
        g_scene->getActiveMesh ()->moveRight (MOVEMENT_DELTA);
      else if (key == GLFW_KEY_3)
        g_scene->getActiveMesh ()->moveUp (-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_4)
        g_scene->getActiveMesh ()->moveUp (MOVEMENT_DELTA);
      else if (key == GLFW_KEY_5)
        g_scene->getActiveMesh ()->moveBack (-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_6)
        g_scene->getActiveMesh ()->moveBack (MOVEMENT_DELTA);
      else if (key == GLFW_KEY_7)
        g_scene->getActiveMesh ()->scaleLocal (1.01f);
      else if (key == GLFW_KEY_8)
        g_scene->getActiveMesh ()->scaleLocal (0.99f);
  
    }
  }
}

void
recordMouse (GLFWwindow* window, int button, int action, int modifiers)
{
  if (action == GLFW_PRESS)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      g_mouseBuffer.setLeftButton (true);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
      g_mouseBuffer.setRightButton (true);
  }
  else if (action == GLFW_RELEASE)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      g_mouseBuffer.setLeftButton (false);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
      g_mouseBuffer.setRightButton (false);
  }
}

void
processMouse (GLFWwindow* window)
{
  double currX, currY;
  glfwGetCursorPos (window, &currX, &currY);

  double scale = 0.05;

  if (g_mouseBuffer.getLeftButton ())
  {
    double x = currX - g_mouseBuffer.getX ();
    double y = currY - g_mouseBuffer.getY ();
    g_camera->yaw (scale * x);
    g_camera->pitch (scale * y);
  }
  else if (g_mouseBuffer.getRightButton ())
  {
    double x = currX - g_mouseBuffer.getX ();
    g_camera->roll (scale * x);
  }

  g_mouseBuffer.setPosition (currX, currY);
}

void
processScroll (GLFWwindow* window, double xOff, double yOff)
{
  g_verticalFov += yOff;
  if (g_verticalFov > 120.f)
    g_verticalFov = 120.f;
  else if (g_verticalFov < 1.0f)
    g_verticalFov = 1.0f;
  g_camera->setProjectionSymmetricPerspective (g_verticalFov, aspectRatio, nearZ, farZ);
}

/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  //g_context->deleteVertexArrays (g_vaos.size (), g_vaos.data ());
  delete g_scene;
  delete g_camera;
  delete g_shaderColorProgram;
  delete g_shaderNormProgram;
  delete g_shaderGenProgram;
  delete g_context;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
