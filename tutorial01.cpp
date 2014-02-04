// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#ifndef __APPLE__
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <iostream>

#include "common/Init.h"
#include "common/Shader.h"

using namespace glm;

int main( void )
{
  
  //Create init object
  Init init = Init();

  //Initialize glfw
  init.glfw(4,1);

  //Open a window
  GLFWwindow* window = init.window();

  //Print window info
  init.printWindowInfo(window);

  //Make opened window current context
  glfwMakeContextCurrent(window);


  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  //Load in shaders
  static ShaderProgram prog("../fragShader.frag", "../vertShader.vert");
        
  do{
    prog();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);


    glfwSwapBuffers(window);
    glfwPollEvents();
  } // Check if the ESC key was pressed or the window was closed
  while( !glfwWindowShouldClose(window) );

  // Close OpenGL window and terminate GLFW
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
