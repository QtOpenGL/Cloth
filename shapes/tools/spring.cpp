#include "spring.h"

Spring::Spring(QVector3D* orig, QVector3D* dest){
  this->origin = orig;
  this->dest = dest;
  QVector3D vec = (*dest-*orig);
  init = &vec;
  i_stretch = init->length();
}
Spring::~Spring(){
}
//returns stretch ratio in vector
float Spring::getStretch(){
  QVector3D vec = (*dest-*origin);
  float curr_stretch = vec.length();
  //negative means compression, positive is stretch
  return curr_stretch/i_stretch - 1;
}
