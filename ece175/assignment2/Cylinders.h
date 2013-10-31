#ifndef CYLINDERS_H
#define CYLINDERS_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <vector>

class Point;
class Cylinder;

/*
GLfloat calcQ(GLfloat p1, GLfloat p2) {
  return (3.0/4.0)*(p1) + (1.0/4.0)*(p2);
}

GLfloat calcR(GLfloat p1, GLfloat p2) {
  return (1.0/4.0)*(p1) + (3.0/4.0)*(p2);
}

void Chaikins(std::vector<Point*>& controlPoints, int level) {
  std::vector<Point*> newPoints;
  if (level) {
    std::vector<Point*>::iterator it = controlPoints.begin();
    Point* current = *it;
    for (it++; it != controlPoints.end(); ++it) {
      Point* next = *it;
      GLfloat Qx = calcQ(current->_x, next->_x);
      GLfloat Qy = calcQ(current->_y, next->_y);
      Point* Q = newPoint(Qx, Qy);

      GLfloat Rx = calcR(current->_x, next->_x);
      GLfloat Ry = calcR(current->_y, next->_y);
      Point* R = newPoint(Rx, Ry);

      newPoints.push_back(Q);
      newPoints.push_back(R);
      current = next;
    }

    Chaikins(newPoints, level - 1);
  } else {
    drawCurve(controlPoints);
  }

  freePoints(controlPoints);
}
*/

class Point {
public:
  GLfloat _x;
  GLfloat _y;
  GLfloat _z;

  Point(GLfloat x, GLfloat y, GLfloat z) :
    _x(x),
    _y(y),
    _z(z) {
  }

  void PrintPoint() {
    printf("Point <%f, %f, %f>\n", _x, _y, _z);
  }
};

class Cylinder {
  public:
    Cylinder(GLfloat radius, GLfloat height) :
      _radius(radius),
      _height(height) {
    }

    void draw() {
      drawTop();
    }

  private:
    GLfloat _radius;
    GLfloat _height;

    void drawTop() {
      // For now don't draw about the Z axis
      GLfloat points = 100.0;
      GLfloat increment = (2.0 * M_PI) / points;
      for (GLfloat theta = 0; theta <= 2.0 * M_PI; theta += increment) {
        // So we rotate about the Z axis now
        GLfloat z = 0.0;
        GLfloat x = cos(theta) * _radius;
        GLfloat y = sin(theta) * _radius;
        GLfloat w = 1.0;
        glVertex4f(x, y, z, w);
      }
    }

    void drawBottom() {

    }

    void drawConnection() {

    }
};


#endif
