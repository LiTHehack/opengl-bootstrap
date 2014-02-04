#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <fstream>
//Blatantly stolen from http://stackoverflow.com/questions/2795044/easy-framework-for-opengl-shaders-in-c-c
class ShaderProgram {
 private:
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


  GLuint compile(GLuint type, const GLchar *const (*source), GLsizei N) {
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
  ShaderProgram(std::string vfileName, std::string ffileName) {
    auto v_source = readFromFile(vfileName);
    auto f_source = readFromFile(ffileName);
    vertex_shader = compile(GL_VERTEX_SHADER, &v_source[0], v_source.size());
    fragment_shader = compile(GL_FRAGMENT_SHADER, &f_source[0], f_source.size());
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
  static const std::vector<const GLchar*> readFromFile(std::string fileName){
    std::ifstream ifs(fileName.c_str());
    std::vector<const GLchar*> vec;
    //This line is currently leaking memory, but it should not be of any concern, since the memory impact should be very low.
    //Could potentially become a problem later on.
    std::string *s = new std::string();
    if(ifs.is_open()){
      while(std::getline(ifs, *s)){
        vec.push_back((s->append("\n\0")).c_str());
      }
      return vec;
    }
    else{
      std::cerr << "Could not open file" << std::endl;
      return vec;
    }
  }
};
