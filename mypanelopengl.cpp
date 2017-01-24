#include "mypanelopengl.h"
#include <cmath>
#include <iostream>
#include <QVector4D>

using namespace std;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QOpenGLWidget(parent) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    m_polymode = 1;

    timer = NULL;
    phase = 0;
    m_angles = vec3(0, 0, 0);

}

MyPanelOpenGL::~MyPanelOpenGL(){
    shaderProgram->release();
    destroyShaders();
    if(timer) {
        delete timer; timer=NULL;
    }
    delete m_sphere;
}

void MyPanelOpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glFrontFace(GL_CW);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders();

    //timer for updating
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->start(30); // trigger every 30ms

    //initialize cloth object
    m_model.setToIdentity();
    m_sphere = new Sphere(vec3(0, 0, -15), 5., 15, 15);
    cloth = new Cloth();

    // /* CAMERA:  eye ---- center ---- up direction */
    shaderProgram->bind();
    camera.lookAt(vec3(0,0, 5),vec3(0,0,0),vec3(0,1,0));
    m_texture = new QOpenGLTexture(QImage(":/build/earth.png").mirrored());
}
// glActiveTexture(GL_TEXTURE0);
void MyPanelOpenGL::step(){
    update(); /* call paint */
}
void MyPanelOpenGL::resizeGL(int w, int h){
    glViewport(0,0,w, h);
}
void MyPanelOpenGL::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updatePolyMode(m_polymode);
    m_texture->bind();
    shaderProgram->setUniformValue("Tex0", 0);

    if(!shaderProgram){return;}

    m_model.setToIdentity();
    m_model.rotate(m_angles.x(), vec3(1,0,0));
    m_model.rotate(m_angles.y(), vec3(0,1,0));
    m_model.rotate(m_angles.z(), vec3(0,0,1));
    mat4 mview = camera * m_model;
    m_projection.setToIdentity();
    m_projection.perspective(65,1,1,15000);
    shaderProgram->setUniformValue("project",m_projection);
    shaderProgram->setUniformValue("camera", camera);
    shaderProgram->setUniformValue("model", m_model);
    shaderProgram->setUniformValue("modelView", mview);
    shaderProgram->setUniformValue("normalMatrix", mview.normalMatrix());
    shaderProgram->setUniformValue("lightPos", vec4(0, 0, 10, 1.));

    cloth->draw(shaderProgram);
    m_sphere->draw(shaderProgram);

    glFlush();
}
void MyPanelOpenGL::keyPressEvent(QKeyEvent *event) {
  QMatrix4x4 m_transform;
  switch (event->key()) {
  case Qt::Key_P:
    m_polymode = (m_polymode + 1) % 3;
    updatePolyMode(m_polymode);
    break;
  case Qt::Key_Left:
      m_transform.translate(2, 0, 0);
      camera = m_transform*camera;
      break;
  case Qt::Key_Right:
      m_transform.translate(-2, 0, 0);
      camera = m_transform*camera;
      break;
  case Qt::Key_Down:
      m_transform.translate(0, 2, 0);
      camera = m_transform*camera;
      break;
  case Qt::Key_Up:
      m_transform.translate(0, -2, 0);
      camera = m_transform*camera;
      break;
  case Qt::Key_O:
      m_transform.translate(0, 0, -2);
      camera = m_transform*camera;
      break;
  case Qt::Key_I:
      m_transform.translate(0, 0, 2);
      camera = m_transform*camera;
      break;
  case Qt::Key_X:
    if (event->text() == "x") {
      updateAngles(0, 15);
    } else {
      updateAngles(0, -15);
    }
    break;
  case Qt::Key_Y:
    if (event->text() == "y") {
      updateAngles(1, 15);
    } else {
      updateAngles(1, -15);
    }
    break;
  case Qt::Key_Z:
    if (event->text() == "z") {
      updateAngles(2, 15);
    } else {
      updateAngles(2, -15);
    }
    break;
  }
 update();
}
void MyPanelOpenGL::updateAngles(int idx, qreal amt) {
  if (idx == 0) {
    m_angles.setX(m_angles.x() + amt);
  } else if (idx == 1) {
    m_angles.setY(m_angles.y() + amt);
  } else if (idx == 2) {
    m_angles.setZ(m_angles.z() + amt);
  }
}
void MyPanelOpenGL::updatePolyMode(int val) {
  GLenum mode = GL_NONE;
  if (val == 0) {
    mode = GL_POINT;
  } else if (val == 1) {
    mode = GL_LINE;
  } else if (val == 2) {
    mode = GL_FILL;
  }

  if (mode != GL_NONE) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
  }
}
void MyPanelOpenGL::createShaders(){
    destroyShaders(); //get rid of any old shaders

    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    if (!vertexShader->compileSourceFile(":/shaders/vshader.glsl")){
        qWarning() << vertexShader->log();
    }

    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!fragmentShader->compileSourceFile(":/shaders/fshader.glsl")){
        qWarning() << fragmentShader->log();
    }

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);

    if(!shaderProgram->link()){
        qWarning() << shaderProgram->log() << endl;
    }

}
void MyPanelOpenGL::destroyShaders(){

    delete vertexShader; vertexShader=NULL;
    delete fragmentShader; fragmentShader=NULL;

    if(shaderProgram){
        shaderProgram->release();
        delete shaderProgram; shaderProgram=NULL;
    }
}
