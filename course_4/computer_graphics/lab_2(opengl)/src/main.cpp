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

void mainLoopHander() {
  int** character_coordinates = game->getCharacterCoordinates();
  char** map = game->getMap();

  if (time_accumulated_ms++ % TIME_DESIRED_LIMIT == 0) {
    for (int character_index = 0; character_index < CHARACTERS_AMOUNT; character_index++) {
      int character_x = character_coordinates[character_index][0];
      int character_y = character_coordinates[character_index][1];

      // change direction if needed
      if (character_index == PACMAN_CHARACTER_INDEX) {
        int* pressed_keys = game->getPressedKeys();
        for (int i = 0; i < 4; i++) {
          if (pressed_keys[i]) {
            switch (i) {
              case KEY_UP:
                if (character_y != 0 && map[character_y + 1][character_x] != '#') {
                  game->changeDirection(character_index, i);
                }
                break;

              case KEY_LEFT:
                if (character_x != 0 && map[character_y][character_x - 1] != '#') {
                  game->changeDirection(character_index, i);
                }
                break;

              case KEY_DOWN:
                if (character_y != MAP_HEIGHT - 1 && map[character_y - 1][character_x] != '#') {
                  game->changeDirection(character_index, i);
                }
                break;

              case KEY_RIGHT:
                if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
                  game->changeDirection(character_index, i);
                }
                break;

              default:
                break;
            }
            break;
          }
        }
      } else {
        int random_ghost_direction = game->getRandomDirection(character_index);
        game->changeDirection(character_index, random_ghost_direction);
      }

      int* character_directions = game->getCharacterDirections();
      int character_direction = character_directions[character_index];
      switch (character_direction) {
        case KEY_UP:
          if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
            character_coordinates[character_index][1]++;
          }
          break;

        case KEY_LEFT:
          if (character_x != 0 && map[character_y][character_x - 1] != '#') {
            character_coordinates[character_index][0]--;
          }
          break;

        case KEY_DOWN:
          if (character_y != 0 && map[character_y - 1][character_x] != '#') {
            character_coordinates[character_index][1]--;
          }
          break;

        case KEY_RIGHT:
          if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
            character_coordinates[character_index][0]++;
          }
          break;

        default:
          break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
//    glLoadIdentity();                 // Reset the model-view matrix
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
  glutIdleFunc(mainLoopHander);

  game = new Game;
  painter = new Painter;

  initGL();                         // Our own OpenGL initialization
  glutMainLoop();                   // Enter the infinite event-processing loop
  return 0;
}