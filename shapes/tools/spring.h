#pragma once

#include "common.h"
#include <QVector3D>

class Spring{
public:
  Spring(QVector3D* orig, QVector3D* dest);
  ~Spring();
  //returns stretch ratio in vector
  float getStretch();

private:
  QVector3D* init;
  float i_stretch;
  QVector3D* origin;
  QVector3D* dest;
};
