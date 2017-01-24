#pragma once

#include <QVector3D>
#include <QVector2D>
#include <vector>

#include "common.h"

typedef QVector3D vec3;
typedef QVector2D vec2;
// #include
class Vertex{

public:

  struct Spring{
    vec3 init;
    float i_stretch;
    Vertex* dest;

  };
  Vertex(int id, vec3 position, vec3 normal, vec2 texture);
  ~Vertex();
  int id;
  vec3 position;
  vec3 velocity;
  vec3 force;
  vec3 normal;
  vec2 texture;
  std::vector<Spring> springs;
  int nsprings;

  //the spring vector at rest
  //the other vertices it is is connected to by a spring
  // vector<Vertex*> springs;
  // //if its static, it will not be affected by forces
  bool isStatic;

  //spring stuff
  void addSpring(Vertex* dest);
  vec3 getSpringForces();
};
