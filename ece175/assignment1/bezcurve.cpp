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

GLfloat ctrlpoints[4][3] = {
  { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
  {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

void drawCurve(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  // the 3 here means we're doing a cubic evaluation
  // Since we're doing a cubic evaluation, we need 4 control points
  // Control points here need a z because we specify GL_MAP1_VERTEX_3
  // glMap1f seems to auto do a bezier curve
  //glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
  //glEnable(GL_MAP1_VERTEX_3);
  // Yup GL_MAP1_VERTEX_3 lets opengl do our curve evaluation instead of us
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

void display(void) {
  int i;

  // Our control points
  Point start(0, -6, -4, 0);
  Point tan1(1, -2, 6, 0);
  Point tan2(2, 2, -4, 0);
  Point end(3, 6, 4, 0);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  // Let's draw it using our own bezier curve
  // Use our own bezier curve function,
  // create a line strip connecting the dots
  glBegin(GL_LINE_STRIP);
  int t = 50;
  for (i = 0; i <= t; i++) {
    float pos = (float) i / (float) t;
    GLfloat x = bezierCurve(pos, start._x, tan1._x, tan2._x, end._x);
    GLfloat y = bezierCurve(pos, start._y, tan1._y, tan2._y, end._y);
    // In our case, the z should always be empty
    GLfloat z = bezierCurve(pos, start._z, tan1._z, tan2._z, end._z);
    
    Point result(4, x, y, z);
    result.PrintPoint();
    glVertex3f(x, y, z);
  }
  glEnd();

  /* The following code displays the control points as dots. */
  /*
  glPointSize(5.0);
  // yellow points!
  glColor3f(1.0, 1.0, 0.0);

  // Draws the points
  glBegin(GL_POINTS);
  for (i = 0; i < 4; i++)
    glVertex3fv(&ctrlpoints[i][0]);
  glEnd();
  */

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

