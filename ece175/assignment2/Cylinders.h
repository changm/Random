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
class Cube;

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

class Cube {
  public:
    Cube(GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2) :
        _x1(x1), _y1(y1), _z1(z1),
        _x2(x2), _y2(y2), _z2(z2) {}

    void print() {
      printf("Printing teh point\n");
    }

    void iterateX() {
      iterateY(_x1);
      iterateY(_x2);
    }

    void iterateY(GLfloat x) {
      iterateZ(x, _y1);
      iterateZ(x, _y2);
    }

    // At the moment let's overdraw
    void iterateZ(GLfloat x, GLfloat y) {
      GLfloat w = 1.0;
      glVertex4f(x, y, _z1, w);
      glVertex4f(x, y, _z2, w);
    }

    void drawXYPlane(GLfloat z) {
      GLfloat w = 1.0;
      // Even though we're doing line segments
      // It has to be in the specific order of
      // the "current" point
      printf("x1 is: %f, x2 is: %f\n", _x1, _x2);

      // Draw bottom line
      glVertex4f(_x2, _y1, z, w);
      glVertex4f(_x1, _y1, z, w);

      // Draw top right
      glVertex4f(_x1, _y1, z, w);
      glVertex4f(_x1, _y2, z, w);

      // Draw top line
      glVertex4f(_x1, _y2, z, w);
      glVertex4f(_x2, _y2, z, w);

      // Draw left line
      glVertex4f(_x2, _y2, z, w);
      glVertex4f(_x2, _y1, z, w);

      // Now we're back at P1(x2, y1, z);
    }

    void connect() {
      // Should be at point (x2, y1, z1);
      // Connect to (x2, y1, z2), go "depth"
      GLfloat w = 1.0;
      printf("Connecting depth: %f to %f\n", _z1, _z2);
      glVertex4f(_x1, _y1, _z1, w);
      glVertex4f(_x1, _y1, _z2, w);
    }

    void connectPlanes() {
      // Should be at (x2, y1, z2);
      GLfloat w = 1.0;
      // Back, bottom negative x
      /*
      glVertex4f(_x2, _y1, _z2, w);
      glVertex4f(_x1, _y1, _z2, w);
      */

      // bottom->bottom front
      glVertex4f(_x2, _y1, _z2, w);
      glVertex4f(_x2, _y1, _z1, w);

      glVertex4f(_x2, _y2, _z1, w);
      glVertex4f(_x2, _y2, _z2, w);

      glVertex4f(_x1, _y2, _z2, w);
      glVertex4f(_x1, _y2, _z1, w);

/*
      // Bottom front -> top front
      glVertex4f(_x1, _y1, _z1, w);
      glVertex4f(_x1, _y2, _z1, w);

      // top front -> top back
      glVertex4f(_x1, _y2, _z1, w);
      glVertex4f(_x1, _y2, _z2, w);

      // top right back -> top left back
      glVertex4f(_x1, _y2, _z2, w);
      glVertex4f(_x2, _y2, _z2, w);

      // Top right back -> top right front
      glVertex4f(_x2, _y2, _z2, w);
      glVertex4f(_x2, _y2, _z1, w);
      */
    }

    // At this point should have the 2 XY squares
    // with 1 line connecting the 2 XY squares
    // through the Z plane
    void draw() {
      drawXYPlane(_z1);
      connect();
      drawXYPlane(_z2);
      // Should be at (x2, y2, z2);
      connectPlanes();
    }

  private:
    GLfloat _x1;
    GLfloat _y1;
    GLfloat _z1;
    GLfloat _x2;
    GLfloat _y2;
    GLfloat _z2;
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
        glVertex4f(x, y, z, 1.0);
      }
    }

    void drawBottom() {
    }

    void drawConnection() {
    }
};


#endif
