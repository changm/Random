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

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  glPointSize(5.0);
  // yellow points!
  glColor3f(1.0, 1.0, 0.0);

  glBegin(GL_LINES);
  Cylinder cylinder(1.0, 3.0);
  //cylinder.draw();

  Cube cube(0, 0, 0,
        4.0, 4.0, 4.0);
  cube.draw();

  glEnd();

  // Always need a flush
  glFlush();
}

// Clip the same
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

  // 90 degrees mean we're looking directly at the circle?
  // at 180 degrees the object disappears, why?
  // NEVAR CLIP
  gluPerspective(80.0, 1.0, 1.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Basically, we have a unit circle around the X/Y axis
  // We start the "eye" at +3
  // We set center to negative from the eye starting point
  // imagine a circle, and we have the eye ball ahead of it
  // and tell the eyeball to look behind it
  // Probably more logical to do the other way but this works
  // In our case, the "up" doesn't amtter as long as its not on the z axis
  // If it is on the Z axis, it's telling our camera up is the same direction
  // we're looking, which doesn't make sense when staring at a circle
  /*
  gluLookAt(0.0, 0.0, 3.0,  // eye starting
            0.0, 0.0, 2.0,  // vector where
            0.0, 1.0, 0.0); // make y axis our "up"
            */
  // Le cube!
  gluLookAt(-1.0, 0.0, -2.0,  // eye starting
            0.0, 0.0, 1.0,  // vector where
            0.0, 1.0, 0.0); // make y axis our "up"
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (600, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);

  drawCurve();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

