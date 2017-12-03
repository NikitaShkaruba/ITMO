#include "lib/include/include.h"

const int TIME_DESIRED_LIMIT = 10000;
int time_accumulated_ms = 0;

Game* game = nullptr;
Painter* painter = nullptr;

void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  glClearDepth(1.0f);                   // Set background depth to farthest
  glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
  glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
  glShadeModel(GL_SMOOTH);              // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void displayHandler() {
  painter->vertices.clear();

  char** map = game->getMap();
  int** character_coordinates = game->getCharacterCoordinates();

  if (game->isGameOver()) {
    painter->drawGameOverScreen();
  } else if (game->isPlayerWins()) {
    painter->drawWinScreen();
  } else {
    painter->drawWorld(map, character_coordinates);
  }

  glVertexPointer(3, GL_FLOAT, 0, NULL);                              // Establish its 3 coordinates per vertex with zero stride in this array; necessary here
  glBufferData(GL_ARRAY_BUFFER, painter->vertices.size() * sizeof(float), painter->vertices.data(), GL_STATIC_DRAW);  // Upload vertex data to the video device
  glBindBuffer(GL_ARRAY_BUFFER, painter->main_vertex_buffer);                  // Make the new VBO active. Repeat here incase changed since initialisation

  glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(painter->vertices.size() / 3 + painter->colors.size() / 3));    // Actually draw the triangle, giving the number of vertices provided

  glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
  glFlush(); // Force display to be drawn now
}

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
  srand(static_cast<unsigned int>(time(NULL)));

  glGenBuffers(1, &painter->main_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, painter->main_vertex_buffer);
  glEnableClientState(GL_VERTEX_ARRAY); // first array for verticies

  initGL();                         // Our own OpenGL initialization
  glutMainLoop();                   // Enter the infinite event-processing loop
  return 0;
}