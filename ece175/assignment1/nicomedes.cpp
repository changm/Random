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

  void PrintPoint() {
    printf("Point %d = <%f, %f, %f>\n", _id, _x, _y, _z);
  }
};

void drawCurve(void) {
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

// Given a polar coordinate r and angle theta
// Return the Cartesian X coordinate
GLfloat polar_x(GLfloat r, GLfloat theta) {
  return r * cos(theta);
}

// Given the polar coordinate r and angle theta
// Return the Cartesian Y cordinate
GLfloat polar_y(GLfloat r, GLfloat theta) {
  return r * sin(theta);
}

void drawPoint(GLfloat a, GLfloat b, GLfloat theta) {
  GLfloat cosine = cos(theta);
  GLfloat r = b + a * (1.0 / cos(theta));
  GLfloat x = polar_x(r, theta);
  GLfloat y = polar_y(r, theta);
  GLfloat z = 0.0;
  glVertex3f(x, y, z);
}

void iterateOverTheta(GLfloat a, GLfloat b) {
  GLfloat theta = 0.0;
  for (theta; theta <= 2 * M_PI; theta += (M_PI / 20)) {
    drawPoint(a, b, theta);
    printf("Theta is: %f\n", theta);
  }

  // So we close the loop
  printf("Last theta: %f\n", theta);
  drawPoint(a, b, theta);
}

void drawNicomedes() {
  GLfloat b = 1.0;
  //iterateOverTheta(-0.5, b);
  for (GLfloat a = -2.0; a < 2.0; a += 0.5) {
    iterateOverTheta(a, b);
  }
}

void display(void) {
  int i;

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  glPointSize(2.0);
  // yellow points!
  glColor3f(1.0, 1.0, 0.0);

  glBegin(GL_LINE_STRIP);
  //glBegin(GL_POINTS);
  drawNicomedes();
  //drawPoint(0.5, 1.0, 1.570796);
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

  drawCurve();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

