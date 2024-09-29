/*
Name(s): Patrick Ekeu
Date: February 9, 2024
Project 1: Memory Game
Description: Create a Memory game featuring a 4x4 grid of cards,
             with the goal to match and remove all pairs. It includes features
             like card flip animations, a turn counter, a right-click menu, and
             robust handling of various scenarios.
*/

#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

// Constants
const int BOARD_SIZE = 4;
const float CARD_WIDTH = 50.0;
const float CARD_HEIGHT = 50.0;
const float SPACE_BETWEEN_CARDS = 10.0;
const float BOARD_OFFSET_X = 50.0;
const float BOARD_OFFSET_Y = 50.0;

// Struct to represent a card
struct Card {
    bool matched;
    bool flipped;
    char symbol; // You can use any symbol you like
};

// 2D array to represent the game board
Card gameBoard[BOARD_SIZE][BOARD_SIZE];

// Variables
int selectedX = -1;
int selectedY = -1;
int turns = 0;

// Function to initialize the game board
void initializeBoard() {
    char symbols[] = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H'};
    srand(time(0));
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int index = rand() % (BOARD_SIZE * BOARD_SIZE - (i * BOARD_SIZE + j));
            gameBoard[i][j].matched = false;
            gameBoard[i][j].flipped = false;
            gameBoard[i][j].symbol = symbols[index];
            symbols[index] = symbols[BOARD_SIZE * BOARD_SIZE - (i * BOARD_SIZE + j) - 1];
        }
    }
}

// Function to draw a card
void drawCard(float x, float y, char symbol, bool flipped) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    if (flipped) {
        glVertex2f(x, y);
        glVertex2f(x + CARD_WIDTH, y);
        glVertex2f(x + CARD_WIDTH, y + CARD_HEIGHT);
        glVertex2f(x, y + CARD_HEIGHT);
    } else {
        glVertex2f(x, y);
        glVertex2f(x + CARD_WIDTH, y);
        glVertex2f(x + CARD_WIDTH, y + CARD_HEIGHT);
        glVertex2f(x, y + CARD_HEIGHT);
    }
    glEnd();

    if (flipped) {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(x + CARD_WIDTH / 2 - 5, y + CARD_HEIGHT / 2);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, symbol);
        glutPostRedisplay();
    }
}

// Function to draw the game board
void drawBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            float x = BOARD_OFFSET_X + j * (CARD_WIDTH + SPACE_BETWEEN_CARDS);
            float y = BOARD_OFFSET_Y + i * (CARD_HEIGHT + SPACE_BETWEEN_CARDS);
            drawCard(x, y, gameBoard[i][j].symbol, gameBoard[i][j].flipped);
        }
    }
}

// Function to check if the game is finished
bool isGameFinished() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!gameBoard[i][j].matched) {
                return false;
            }
        }
    }
    return true;
}

// Function to handle mouse clicks
void handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int col = (x - BOARD_OFFSET_X) / (CARD_WIDTH + SPACE_BETWEEN_CARDS);
        int row = (y - BOARD_OFFSET_Y) / (CARD_HEIGHT + SPACE_BETWEEN_CARDS);

        if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE && !gameBoard[row][col].flipped) {
            if (selectedX == -1 && selectedY == -1) {
                selectedX = col;
                selectedY = row;
                gameBoard[row][col].flipped = true;
                glScalef(1, 1, -1);
            } else {
                gameBoard[row][col].flipped = true;
                turns++;

                if (gameBoard[row][col].symbol == gameBoard[selectedY][selectedX].symbol) {
                    gameBoard[row][col].matched = true;
                    gameBoard[selectedY][selectedX].matched = true;
                } else {
                    gameBoard[row][col].flipped = false;
                    gameBoard[selectedY][selectedX].flipped = false;
                }

                selectedX = -1;
                selectedY = -1;
            }
        }
    }
}

// Function to handle timer events
void handleTimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000, handleTimer, 0);

    if (isGameFinished()) {
        std::cout << "Game Over! Turns: " << turns << std::endl;
        exit(0);
    }
}

// Function to handle drawing
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBoard();

    glutSwapBuffers();
}

// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Function to create the menu
void createMenu() {
    glutCreateMenu([](int value) {
        if (value == 1) {
            initializeBoard();
            turns = 0;
            selectedX = -1;
            selectedY = -1;
        } else if (value == 2) {
            exit(0);
        }
        else if (value == 3)
        {
            //Slows the card down
        }
    });

    glutAddMenuEntry("Restart", 1);
    glutAddMenuEntry("Quit", 2);
    glutAddMenuEntry("Decrease Speed Animation", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Memory Game");
    glutInitWindowSize(600, 600);

    initializeBoard();
    createMenu();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseClick);
    glutTimerFunc(0, handleTimer, 0);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutMainLoop();

    return 0;
}
