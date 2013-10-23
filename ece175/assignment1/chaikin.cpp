#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <vector>

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

void drawCurve(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

GLfloat calcQ(GLfloat p1, GLfloat p2) {
  return (3.0/4.0)*(p1) + (1.0/4.0)*(p2);
}

GLfloat calcR(GLfloat p1, GLfloat p2) {
  return (1.0/4.0)*(p1) + (3.0/4.0)*(p2);
}

void freePoints(std::vector<Point*>& points) {
  std::vector<Point*>::iterator it;
  for (it = points.begin(); it != points.end(); ++it) {
    Point* p = *it;
    delete p;
  }
}

Point* newPoint(GLfloat x, GLfloat y) {
  return new Point(x, y, 0.0);
}

void drawCurve(std::vector<Point*>& controlPoints) {
  glBegin(GL_LINE_STRIP);
  std::vector<Point*>::iterator it = controlPoints.begin();
  for (it; it != controlPoints.end(); ++it) {
    Point* p = *it;
    glVertex3f(p->_x, p->_y, p->_z);
  }
  glEnd();
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

void display(void) {
  int i;

  // Our control points
  Point* start = newPoint(0.0, 0.0);
  Point* end = newPoint(0.0, 4.0);
  Point* right = newPoint(4.0, 4.0);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  glPointSize(5.0);
  // yellow points!
  glColor3f(1.0, 1.0, 0.0);

  std::vector<Point*> controlPoints;
  controlPoints.push_back(start);
  controlPoints.push_back(end);
  controlPoints.push_back(right);

  int level = 3;
  Chaikins(controlPoints, level);

  // Always need a flush
  glFlush();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho scales the matrix by multiplying the matrix
  if (w <= h) {
    glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
        5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
  } else {
    glOrtho(-5.0*(GLfloat)w/(GLfloat)h,
        5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (640, 480);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);

  drawCurve();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

