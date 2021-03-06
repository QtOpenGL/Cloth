#pragma once

#include <QVector3D>
#include <QVector2D>
#include <ostream>

typedef QVector3D vec3;
typedef QVector2D vec2;

/* Print QVector3d objects using cout. */
std::ostream &operator<<(std::ostream &str, const QVector3D &vec);
