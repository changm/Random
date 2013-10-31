#include "Cylinders.h"

void drawCurve(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
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

  glBegin(GL_POINTS);
  Cylinder cylinder(2.0, 3.0);
  cylinder.draw();
  glEnd();

  // Always need a flush
  glFlush();
}

void clip(int w, int h) {
  GLfloat left = -5.0;
  GLfloat right = 5.0;
  GLfloat near = -5.0;
  GLfloat far = 5.0;

  if (w <= h) {
    GLfloat bottom = -5.0 * ((GLfloat)h / (GLfloat) w);
    GLfloat top = 5.0 * ((GLfloat)h / (GLfloat) w);
    glOrtho(left, right, bottom, top, near, far);
  } else {
    // Why is left fliipped? And why is w/h flipped?
    //  Seems to make no difference...
    //left = -5.0 * (GLfloat)w/(GLfloat)h;
    //right = 5.0 * (GLfloat)w/(GLfloat)h;
    GLfloat bottom = -5.0;
    GLfloat top = 5.0;
    glOrtho(left, right, bottom, top, near, far);
  }
}

void reshape(int w, int h) {
  clip(w, h);
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  clip(w, h);

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

