#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "classes/CobraUnit.h" //<CobraUnit.h>
using namespace std;

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
static int step = 10;
CobraUnit generateCobraUnit(int x, int y)
{
    CobraUnit auxcobra;
    auxcobra.setPosicaoX(x);
    auxcobra.setPosicaoY(y);
    auxcobra.setSize(size_default);
    return auxcobra;
}

void init(void);
void display(void);

void drawCobra();
void drawFood();
void reshape(int w, int h);

void wallColision();
void foodColision();
void cobraColision();
void handleColision();

static GLfloat spin = 0.0;

static int head_x = 250;
static int head_y = 250;

static int food_x = rand() % 498 + 1;
static int food_y = rand() % 498 + 1;

static int LEVEL = 1;

static bool IS_THERE_FOOD = true;

static bool LEFT = false;
static bool RIGHT = false;
static bool UP = false;
static bool DOWN = false;

static float r = 1;
static float g = 0;
static float b = 0;

static CobraUnit head = generateCobraUnit(head_x, head_y);
static CobraUnit body1 = generateCobraUnit(250 + 10, 250);
static CobraUnit body2 = generateCobraUnit(250 + 20, 250);
static CobraUnit body3 = generateCobraUnit(250 + 30, 250);
static CobraUnit body4 = generateCobraUnit(250 + 40, 250);
static CobraUnit body5 = generateCobraUnit(250 + 50, 250);
static CobraUnit cobra[2500]; // = {head, body1, body2, body3, body4, body5};

// void mouse(int button, int state, int x, int y);
void addUnitToCobra();

void addUnitToCobra()
{
    cobra[LEVEL] = generateCobraUnit(head_x + 10, head_y);
    LEVEL++;
}
void keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);

void wallColision()
{
    if (head_x >= 500) // direita
    {
        head_x = 0;
    }
    else if (head_x + 10 <= 0) // direita
    {
        head_x = 500;
    }

    if (head_y >= 500)
    {
        head_y = 0;
    }
    else if (head_y + 10 <= 0)
    {
        head_y = 500;
    }
}

void drawFood()
{
    glColor3f(1, 0, 0);
    glRecti(food_x, food_y, food_x + 10, food_y + 10);
    glFlush();
}

void foodColision()
{

    if (!IS_THERE_FOOD)
    {
        food_x = rand() % 498 + 1;
        food_y = rand() % 498 + 1;
        IS_THERE_FOOD = true;
    }

    // two = food
    //one = cobra;
    bool collisionX = head_x + size_default >= food_x &&
                      food_x + size_default >= head_x;
    // Collision y-axis?
    bool collisionY = head_y + size_default >= food_y &&
                      food_y + size_default >= head_y;

    if (collisionX && collisionY)
    { // colision

        addUnitToCobra();
        IS_THERE_FOOD = false;
    }
}

void handleColision()
{
    foodColision();
    wallColision();
}

void cobraCounter();

void cobraCounter()
{
    // sleep(1);
    if (LEFT)
    {
        head_x -= step;
    }
    else if (RIGHT)
    {
        head_x += step;
    }
    else if (UP)
    {
        head_y += step;
    }
    else if (DOWN)
    {
        head_y -= step;
    }
    handleColision();

    for (int i = LEVEL; i > 0; i--)
    {

        if (i == 1)
        {
            cobra[0].setPosicaoX(head_x);
            cobra[0].setPosicaoY(head_y);
        }

        if (i == 0)
        {
            continue;
        }
        else
        {
            int aux_x = cobra[i - 1].getPosicaoX();
            int aux_y = cobra[i - 1].getPosicaoY();

            cobra[i].setPosicaoX(aux_x);
            cobra[i].setPosicaoY(aux_y);
        }
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    // for (int i = 0; i < 2499; i++)
    // {
    cobra[0] = generateCobraUnit(head_x, head_y);
    // }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake 2d- André");
    init();
    // printf("%lu   ", sizeof(CobraUnit));

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutIdleFunc(cobraCounter);
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

void display(void)
{
    // printf("%lu  ", sizeof(CobraUnit));

    glClear(GL_COLOR_BUFFER_BIT);

    drawFood();
    drawCobra();

    glutSwapBuffers();
}

void drawCobra()
{
    // paredes
    // glBegin(GL_LINE_STRIP);
    // glVertex2i(0, 0);
    // glVertex2i(0, 500);
    // glVertex2i(500, 500);
    // glVertex2i(500, 0);
    // glVertex2i(0, 0);
    // glEnd();

    for (int i = 0; i < LEVEL; i++)
    {

        int x = cobra[i].getPosicaoX();
        int y = cobra[i].getPosicaoY();
        int s = cobra[i].getSize();
        glColor3f(0, 0, 0);

        glRecti(x, y, x + s, y + s);
        // glEnd();
        glFlush();
    }
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
        LEFT = false;
        RIGHT = false;
        UP = false;
        DOWN = false;
        break;
    }
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_LEFT:
        if (!RIGHT)
        {
            LEFT = true;
            RIGHT = false;
            UP = false;
            DOWN = false;
        }

        break;

    case GLUT_KEY_RIGHT:
        if (!LEFT)
        {
            LEFT = false;
            RIGHT = true;
            UP = false;
            DOWN = false;
        }
        break;

    case GLUT_KEY_UP:
        if (!DOWN)
        {
            LEFT = false;
            RIGHT = false;
            UP = true;
            DOWN = false;
        }
        break;

    case GLUT_KEY_DOWN:
        if (!UP)
        {
            LEFT = false;
            RIGHT = false;
            UP = false;
            DOWN = true;
        }
        break;
    }
}
