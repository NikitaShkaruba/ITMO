#include "lib/include/include.h"

const int TIME_DESIRED_LIMIT = 100;
int time_accumulated_ms = 0;

WorldEngine* world_engine = nullptr;
Painter* painter = nullptr;

/* Initialize OpenGL Graphics */
void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
  glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
  glShadeModel(GL_SMOOTH);              // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void displayHandler() {
  char** map = world_engine->getMap();
  int** character_coordinates = world_engine->getCharacterCoordinates();

  painter->drawWorld(map, character_coordinates);

  glEnd();   // Done drawing the pyramid
  glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshapeHandler(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
  // Compute aspect ratio of the new window
  if (height == 0) height = 1;                // To prevent divide by 0
  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  // Set the viewport to cover the new window
  glViewport(0, 0, width, height);

  // Set the aspect ratio of the clipping volume to match the viewport
  glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
  glLoadIdentity();             // Reset
  // Enable perspective projection with fovy, aspect, zNear and zFar
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyPressHandler(unsigned char key, int x, int y) {
  int** character_coordinates = world_engine->getCharacterCoordinates();
  int pacman_x = character_coordinates[0][0];
  int pacman_y = character_coordinates[0][1];

  if (key == 'w') {
    world_engine->setCharacterCoordinates(0, pacman_x, pacman_y + 1);
  } else if (key == 'a') {
    world_engine->setCharacterCoordinates(0, pacman_x - 1, pacman_y);
  } else if (key == 's') {
    world_engine->setCharacterCoordinates(0, pacman_x, pacman_y - 1);
  } else if (key == 'd') {
    world_engine->setCharacterCoordinates(0, pacman_x + 1, pacman_y);
  }
};

void mainLoopHander() {
  if (time_accumulated_ms++ % TIME_DESIRED_LIMIT == 0) {
    glutPostRedisplay();
  }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
  glutInit(&argc, argv);            // Initialize GLUT

  glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
  glutInitWindowSize(640, 480);     // Set the window's initial width & height
  glutInitWindowPosition(50, 50);   // Position the window's initial top-left corner

  glutCreateWindow("3D Shapes");    // Create window with the given title
  glutDisplayFunc(displayHandler);         // Register callback handler for window re-paint event
  glutReshapeFunc(reshapeHandler);         // Register callback handler for window re-size event
  glutKeyboardFunc(keyPressHandler);
  glutIdleFunc(mainLoopHander);

  world_engine = new WorldEngine;
  painter = new Painter;

  initGL();                         // Our own OpenGL initialization
  glutMainLoop();                   // Enter the infinite event-processing loop
  return 0;
}