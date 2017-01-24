#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QtWidgets>
#include <QtOpenGL>
#include "shapes/sphere.h"
#include "shapes/cloth.h"

typedef QVector3D vec3;
typedef QVector4D vec4;
typedef QMatrix4x4 mat4;

class MyPanelOpenGL : public QOpenGLWidget
{

    Q_OBJECT

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:
    void setupVAO();
    void createShaders();
    void destroyShaders();
    void createVBOs();
    void destroyVBOs();



    /* update Euler angle at index idx by amt
     * idx=0,1,2 -> x,y,z */
    void updateAngles(int idx, qreal amt);
    /* update Polygon draw mode based
     * 0 : point
     * 1 : line
     * 2 : polygon */
    void updatePolyMode(int val);

    QTimer* timer;
    float phase;

    Sphere* m_sphere;
    Cloth* cloth;


    int m_polymode;

    //view matrix
    QMatrix4x4 m_model;
    QMatrix4x4 camera;
    QMatrix4x4 m_projection;
    vec3 m_angles;

    QOpenGLTexture* m_texture;


    QOpenGLShader *vertexShader;
    QOpenGLShader *fragmentShader;
    QOpenGLShaderProgram *shaderProgram;

signals:

public slots:
    /* called everytime timer fires */
    void step();

};

#endif // MYPANELOPENGL_H
