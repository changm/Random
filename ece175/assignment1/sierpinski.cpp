#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>

class Point {
public:
  int _id;
  GLfloat _x;
  GLfloat _y;
  GLfloat _z;

  Point(int id, GLfloat x, GLfloat y, GLfloat z) :
    _id(id),
    _x(x),
    _y(y),
    _z(z) {
  }

  Point(GLfloat x, GLfloat y, GLfloat z) :
    _id(-1),
    _x(x),
    _y(y),
    _z(z) {
  }

  void PrintPoint() {
    printf("Point %d = <%f, %f, %f>\n", _id, _x, _y, _z);
  }

  void addVector(GLfloat x, GLfloat y, GLfloat z) {
    _x += x;
    _y += y;
    _z += z;
  }

  void addVector(GLfloat x, GLfloat y) {
    addVector(x, y, 0.0);
  }
};

void initCurve(void) {
  // Just init
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

GLfloat bezierCurve(float t, GLfloat P0,
                  GLfloat P1, GLfloat P2, GLfloat P3) {
  // Cubic bezier Curve
  GLfloat point = (pow((1-t), 3.0) * P0) +
    (3 * pow((1-t),2) * t * P1) +
    (3 * (1-t) * t * t * P2) +
    (pow(t, 3) * P3);
  return point;
}

static float distance;
static const int levels = 1;

// Draws a line segment from "current"
// pointer that has to be kept track of elsewhere
// and the new point
void drawLineRel(Point* end) {
  glVertex3f(end->_x, end->_y, end->_z);
}

// Assume z 0 for now
void drawLineRel(Point* current, GLfloat x, GLfloat y) {
  current->addVector(x, y);
  drawLineRel(current);
}

void sierpA(Point* current, int level) {
  if (level) {
    drawLineRel(current, distance, distance);
    drawLineRel(current, 2 * distance, 0);
    drawLineRel(current, distance, -distance);
}
}

void sierpB(Point* current, int level) {
  if (level) {
    drawLineRel(current, -distance, distance);
    drawLineRel(current, 0, 2 * distance);
    drawLineRel(current, distance, distance);
  }
}

void sierpC(Point* current, int level) {
  if (level) {
    drawLineRel(current, -distance, -distance);
    drawLineRel(current, -2 * distance, 0);
    drawLineRel(current, -distance, distance);
  }
}

void sierpD(Point* current, int level) {
  if (level) {
    drawLineRel(current, distance, -distance);
    drawLineRel(current, 0, -2 * distance);
    drawLineRel(current, -distance, -distance);
  }
}

void display(void) {
  int i;

  // Play with this for a while
  distance = 1.0;
  Point current(-3, -3, 0);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  // Let's draw it using our own bezier curve
  // Use our own bezier curve function,
  // create a line strip connecting the dots
  glBegin(GL_LINE_STRIP);
  drawLineRel(&current);

  int level = levels;
  // Recursive sierp
  sierpA(&current, level);
  drawLineRel(&current, distance, distance);

  sierpB(&current, level);
  drawLineRel(&current, -distance, distance);

  sierpC(&current, level);
  drawLineRel(&current, -distance, -distance);

  sierpD(&current, level);
  drawLineRel(&current, distance, -distance);

  glEnd();

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

  initCurve();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

