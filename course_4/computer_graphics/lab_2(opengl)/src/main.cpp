#include "lib/include/include.h"

const int TIME_DESIRED_LIMIT = 10000;
int time_accumulated_ms = 0;

Game* game = nullptr;
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
  char** map = game->getMap();
  int** character_coordinates = game->getCharacterCoordinates();

  if (game->isGameOver()) {
    painter->drawGameOverScreen();
  } else if (game->isPlayerWins()) {
    painter->drawWinScreen();
  } else {
    painter->drawWorld(map, character_coordinates);
  }

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

void keyDownHandler(unsigned char key, int x, int y) {
  if (key == 'w') {
    game->setKeyPress(KEY_UP, 1);
  } else if (key == 'a') {
    game->setKeyPress(KEY_LEFT, 1);
  } else if (key == 's') {
    game->setKeyPress(KEY_DOWN, 1);
  } else if (key == 'd') {
    game->setKeyPress(KEY_RIGHT, 1);
  }
};

void keyUpHandler(unsigned char key, int x, int y) {
  if (key == 'w') {
    game->setKeyPress(KEY_UP, 0);
  } else if (key == 'a') {
    game->setKeyPress(KEY_LEFT, 0);
  } else if (key == 's') {
    game->setKeyPress(KEY_DOWN, 0);
  } else if (key == 'd') {
    game->setKeyPress(KEY_RIGHT, 0);
  }
};

void mainLoopHandler() {
  if (time_accumulated_ms++ % TIME_DESIRED_LIMIT == 0 && !game->isGameOver() && !game ->isPlayerWins()) {
    game->tick();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
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
  glutKeyboardFunc(keyDownHandler);
  glutKeyboardUpFunc(keyUpHandler);
  glutIdleFunc(mainLoopHandler);

  game = new Game;
  painter = new Painter;

  initGL();                         // Our own OpenGL initialization
  glutMainLoop();                   // Enter the infinite event-processing loop
  return 0;
}