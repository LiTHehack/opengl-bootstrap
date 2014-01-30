#pragma once

#include <GLFW/glfw3.h>
//Blatantly stolen from http://stackoverflow.com/questions/2795044/easy-framework-for-opengl-shaders-in-c-c
class ShaderProgram {
  GLuint vertex_shader, fragment_shader, prog;
  std::string getShaderType(GLuint type){
    std::string name;
    switch(type){
    case GL_VERTEX_SHADER:
      name = "Vertex Shader";
      break;
    case GL_FRAGMENT_SHADER:
      name = "Fragment Shader";
      break;
    default:
      name = "Unknown Shader type";
      break;
    }
    return name;
  }
  template <int N>
  GLuint compile(GLuint type, char const *(&source)[N]) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, N, source, NULL);
    glCompileShader(shader);
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      GLint length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      std::string log(length, ' ');
      glGetShaderInfoLog(shader, length, &length, &log[0]);
      std::cerr << "Failed to compile shadertype: "+ getShaderType(type) << std::endl
                << log << std::endl;
      exit(EXIT_FAILURE);
      return false;
    }
    return shader;
  }
public:
  template <int N, int M>
  ShaderProgram(GLchar const *(&v_source)[N], GLchar const *(&f_source)[M]) {
    vertex_shader = compile(GL_VERTEX_SHADER, v_source);
    fragment_shader = compile(GL_FRAGMENT_SHADER, f_source);
    prog = glCreateProgram();
    glAttachShader(prog, vertex_shader);
    glAttachShader(prog, fragment_shader);
    glLinkProgram(prog);
  }

  operator GLuint() { return prog; }
  void operator()() { glUseProgram(prog); }

  ~ShaderProgram() {
    glDeleteProgram(prog);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
  }
};
