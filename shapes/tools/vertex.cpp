#include "vertex.h"
#include <iostream>
#include <math.h>

using namespace std;
Vertex::Vertex(int id, vec3 position, vec3 normal, vec2 texture){
  this->id = id;
  this->position = position;
  velocity = vec3(0,0,0);
  force = vec3(0,0,0);
  this->normal = normal;
  this->texture = texture;
  isStatic = true;
}
Vertex::~Vertex(){

}
void Vertex::addSpring(Vertex* dest){
  Spring s;
  s.dest = dest;
  s.init = dest->position - position;
  s.i_stretch = s.init.length();
  springs.push_back(s);
}
vec3 Vertex::getSpringForces(){
//   vec3 springForces(0,0,0);
//   for (int i = 0; i < v->atRest.size(); i++){
//   //Young's modulus -----------------------------------
//   vec3 u = v->springs[i]->position - v->position;
//   float E = 1.5;
//   float uLength = fabs(u.length());
//   float iLength = fabs(v->atRest[i].length());
//   //ratio between orig distance and curr distance
//   float lratio = (uLength/iLength)-1;
//   float stiffnessForce = 0;
//   stiffnessForce =  E*lratio;
//
//   //Damping parameter
//   float d = .0;
//   vec3 vel = v->velocity - v->springs[i]->velocity;
//   float damping = d*(QVector3D::dotProduct(vel,u/uLength));
//
//   springForces += (stiffnessForce+damping)*u/uLength;
  vec3 springForces(0,0,0);
  for (int i = 0; i < springs.size(); i++){
      //Young's modulus -----------------------------------
      vec3 u = springs[i].dest->position - position;
      float E = 1.5;
      float uLength = fabs(u.length());
      float iLength = fabs(springs[i].i_stretch);
      //ratio between orig distance and curr distance
      float lratio = (uLength/iLength)-1;
      float stiffnessForce = E*lratio;
      springForces += stiffnessForce*u/uLength;
  }
  return springForces;
}
