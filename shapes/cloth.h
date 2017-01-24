#pragma once


#include <QtOpenGL>
#include <cmath>
#include <iostream>
#include "sphere.h"
#include "tools/common.h"
#include "tools/ray.h"
#include "tools/vertex.h"
#include <QOpenGLShaderProgram>

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;

class Cloth{

public:
  Cloth();
  ~Cloth();
  void update(float delta);
  void draw(QOpenGLShaderProgram* prog);
  // void update(Sphere* spheres, int amount);

private:
  bool initVBO();
  void updateVBO();
  void setupVAO(QOpenGLShaderProgram* prog);
  // QVector3D getSpringForces(Vertex* v);
  // QVector3D getSelfColForces(Vertex* v);
  // QVector3D getObjColForces(Vertex* v, Sphere* spheres, int amount);

protected:
  Vertex*** verts;
  vec4 m_color;
  QVector3D gravity;
  int length, width, data, nverts, ninds;

  bool firstDraw;
  vec3* vertices;
  vec3* normals;
  vec2* texture;
  unsigned short* indices;
  QOpenGLBuffer *m_ebo;
  QOpenGLBuffer *m_vbo;
  QOpenGLVertexArrayObject *m_vao;
};
