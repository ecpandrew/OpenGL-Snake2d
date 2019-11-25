#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>
#include <iostream>
// #include "classes/CobraUnit.h" //<CobraUnit.h>
using namespace std;
#define PI 3.14159265

class CobraUnit
{

public:
    void setPosicaoX(int x);
    void setPosicaoY(int y);
    int getPosicaoX();
    int getPosicaoY();

    void setSize(int x);
    int getSize();

private:
    int x;
    int y;
    int size;
};
void CobraUnit::setPosicaoX(int pos)
{
    x = pos;
}

void CobraUnit::setPosicaoY(int pos)
{
    y = pos;
}

int CobraUnit::getPosicaoX()
{
    return x;
}

int CobraUnit::getPosicaoY()
{
    return y;
}

void CobraUnit::setSize(int s)
{
    size = s;
}

int CobraUnit::getSize()
{
    return size;
}

CobraUnit generateCobraUnit(int x, int y);
static int size_default = 10;

CobraUnit generateCobraUnit(int x, int y)
{
    CobraUnit cobra;
    cobra.setPosicaoX(x);
    cobra.setPosicaoY(y);
    cobra.setSize(size_default);
    return cobra;
}

void init(void);
void display(void);
void display_helice(void);
void drawHelix();
void drawPoste();
void spinDisplay(void);
void reshape(int w, int h);

static GLfloat spin = 0.0;

static bool UP = false;
static bool JUMP_UP = false;
static int initial_y = 200;
static int limit = 360;
static int ground = 50;
static int xi = 50;
static int xf = 50 + 22;
static int yi = initial_y;
static int yf = 200 + 100;
static int step = 17;

// void mouse(int button, int state, int x, int y);

void keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);

void jump();

void jump()
{

    if (JUMP_UP)
    {
        yi += step;
        yf += step;
        if (yi > limit)
        {
            JUMP_UP = false;
        }
    }
    else
    {

        if (yi == initial_y)
        {
        }
        else
        {
            yi -= step;
            yf -= step;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake 2d- André");
    init();

    glutDisplayFunc(display_helice);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutIdleFunc(jump);
    // glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(1, 1, 1, 1);
    glOrtho(0, 500, 0, 500, -1, 1);
    glShadeModel(GL_FLAT);
}

void display_helice(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawPoste();

    glutSwapBuffers();
}

void drawPoste()
{

    glColor3f(0, 0, 0);

    glRecti(xi, yi, xf, yf);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-50.0, 50.0, -50.0, 50.0 , -1.0, 1.0);

    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)

{
    switch (key)
    {

    case 27:
        exit(0);
        break;
    }
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_UP:
        JUMP_UP = true;
        break;
    }
}
