#include <GL/freeglut.h>
#include <stdio.h>
#include <string>

//Para maiores informações, ver documentação
//http://docs.gl/gl3/

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
static bool ENDGAME = false;
GLuint texid1;

CobraUnit generateCobraUnit(int x, int y)
{
    CobraUnit auxcobra;
    auxcobra.setPosicaoX(x);
    auxcobra.setPosicaoY(y);
    auxcobra.setSize(size_default);
    return auxcobra;
}

// void init(void);
// void display(void);

void drawCobra();
void drawFood();
// void reshape(int w, int h);

void wallColision();
void foodColision();
void cobraColision();
void handleColision();
void stopGame();

void colocaImagem();
GLuint carregaTextura();
char *carrega_bmp();

static GLfloat spin = 0.0;
int w, h, window, fim = 0;

static int head_x = 250;
static int head_y = 250;

static int food_x = rand() % 498 + 1;
static int food_y = rand() % 498 + 1;

static int big_food_x = rand() % 498 + 1;
static int big_food_y = rand() % 498 + 1;

static int LEVEL = 1;
static int DELAY = 30;

static bool IS_THERE_FOOD = true;
static bool IS_THERE_BIG_FOOD = true;

static bool LEFT = false;
static bool RIGHT = false;
static bool UP = false;
static bool DOWN = false;

static float r = 1;
static float g = 0;
static float b = 0;
float angulo = 0.0f, rotX = 1.0, rotY = 0.0f, rotZ = 0.0f, velocidade = -1.00;
// int w, h, window, fim = 0;

static CobraUnit head = generateCobraUnit(head_x, head_y);
// static CobraUnit body1 = generateCobraUnit(250 + 10, 250);
// static CobraUnit body2 = generateCobraUnit(250 + 20, 250);
// static CobraUnit body3 = generateCobraUnit(250 + 30, 250);
// static CobraUnit body4 = generateCobraUnit(250 + 40, 250);
// static CobraUnit body5 = generateCobraUnit(250 + 50, 250);
static CobraUnit cobra[2500]; // = {head, body1, body2, body3, body4, body5};

// void mouse(int button, int state, int x, int y);
void addUnitToCobra();

void addUnitToCobra()
{
    //     if(UP || DOWN ){
    //         CobraUnit piece = generateCobraUnit(0,0);
    //         piece.setPosicaoX(cobra[LEVEL-1].getPosicaoX()-10);
    //         piece.setPosicaoX();
    cobra[LEVEL] = generateCobraUnit(head_x + 1000, head_y);

    // }else{

    // }
    LEVEL++;
}
void keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void stopGame()
{
    printf("\n\nGame stopped\n\n");

    LEFT = false;
    RIGHT = false;
    UP = false;
    DOWN = false;
    head_x = 250;
    head_y = 250;
    LEVEL = 1;
}
void wallColision()
{
    if (head_x >= 500) // direita
    {
        head_x = 0;
        // stopGame();
    }
    else if (head_x + 10 <= 0) // direita
    {
        head_x = 500;
        // stopGame();
    }

    if (head_y >= 500)
    {
        head_y = 0;
        // stopGame();
    }
    else if (head_y + 10 <= 0)
    {
        head_y = 500;
        // stopGame();
    }
}

void drawFood()
{

    glColor3f(1, 0, 0);
    glRecti(food_x, food_y, food_x + 10, food_y + 10);

    // if (!IS_THERE_BIG_FOOD)
    // {
    //     int i = rand() % 100 + 1;

    //     if (0 < i < 50)
    //     {
    //         big_food_x = rand() % 497;
    //         big_food_y = rand() % 497;
    //         glColor3f(0, 1, 0);

    //         glRecti(big_food_x, big_food_y, big_food_x + 20, big_food_y + 20);
    //     }
    // }

    // glFlush();
}

void cobraColision()
{
    int aux_x, aux_y, i;

    for (i = 1; i < LEVEL; i++)
    {
        aux_x = cobra[i].getPosicaoX();
        aux_y = cobra[i].getPosicaoY();

        bool collisionX = head_x + size_default >= aux_x &&
                          aux_x + size_default >= head_x;
        // Collision y-axis?
        bool collisionY = head_y + size_default >= aux_y &&
                          aux_y + size_default >= head_y;

        //     bool collisionX = head_x + size_default >= food_x &&
        //                   food_x + size_default >= head_x;
        // // Collision y-axis?
        //     bool collisionY = head_y + size_default >= food_y &&
        //                   food_y + size_default >= head_y;

        if (collisionX && collisionY)
        { // colision
            stopGame();
        }
    }
}

void foodColision()
{

    if (!IS_THERE_FOOD)
    {
        food_x = rand() % 497;
        food_y = rand() % 497;
        IS_THERE_FOOD = true;
    }
    // if (!IS_THERE_BIG_FOOD)
    // {
    //     big_food_x = rand() % 497;
    //     big_food_y = rand() % 497;
    //     IS_THERE_BIG_FOOD = true;
    // }

    // two = food
    //one = cobra;
    bool collisionX = head_x + size_default >= food_x &&
                      food_x + size_default >= head_x;
    // Collision y-axis?
    bool collisionY = head_y + size_default >= food_y &&
                      food_y + size_default >= head_y;

    // bool bigCollisionX = head_x + size_default >= big_food_x &&
    //                      big_food_x + size_default >= head_x;
    // // Collision y-axis?
    // bool bigCollisionY = head_y + size_default >= big_food_y &&
    //                      big_food_y + size_default >= head_y;

    if (collisionX && collisionY)
    { // colision
        printf("\nFOOD ATED\n");

        addUnitToCobra();
        IS_THERE_FOOD = false;
    }
    // if (bigCollisionX && bigCollisionY)
    // { // colision
    //     printf("\nFOOD ATED\n");

    //     addUnitToCobra();
    //     addUnitToCobra();
    //     addUnitToCobra();
    //     IS_THERE_BIG_FOOD = false;
    // }
}

void handleColision()
{
    foodColision();
    wallColision();
    // cobraColision();
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
    int i, j = 0;

    for (i = 0; i < LEVEL; i++)
    {

        int x = cobra[i].getPosicaoX();
        int y = cobra[i].getPosicaoY();
        int s = cobra[i].getSize();
        glColor3f(0, 0, 0);

        glRecti(x, y, x + s, y + s);
        // glColor3f(1, 1, 1);e

        // glEnd();

        // glFlush();
    }
}
void cobraCounter(int value);

void cobraCounter(int value)
{
    // sleep(0.5);
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
    if (LEVEL == 1)
    {
        addUnitToCobra();
        IS_THERE_FOOD = false;
    }
    printf("LEVEL: %i ;Cobra andou  X : %i Y : %i \n", LEVEL, head_x, head_y);

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
    glutTimerFunc(DELAY, cobraCounter, 1);
}

//Para maiores informações sobre a estrutura de um arquivo bmp, ver "http://easygrid.ic.uff.br/~aconci/curso/bmp.pdf"
char *carrega_bmp()
{
    FILE *f = fopen("solo.bmp", "rb");
    if (f == NULL)
    {
        printf("Erro ao carregar o arquivo %s!", "Textura.bmp");
        exit(1);
    }
    int of;
    fseek(f, 10, SEEK_SET);
    fread(&of, sizeof(int), 1, f);
    fseek(f, 4, SEEK_CUR);
    fread(&w, sizeof(int), 1, f);
    fread(&h, sizeof(int), 1, f);

    fseek(f, of, SEEK_SET);

    int by = ((w * 3 + 3) / 4) * 4 - (w * 3 % 4);
    char *tmp_m = (char *)malloc(sizeof(char) * by * h);
    char *m = (char *)malloc(sizeof(char) * w * h * 3);
    fread(tmp_m, sizeof(char) * by * h, 1, f);
    int x, y, i;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            for (i = 0; i < 3; i++)
            {
                m[3 * (w * y + x) + i] = tmp_m[3 * (w * y + x) + (2 - i)];
            }
        }
    }
    free(tmp_m);
    return m;
}

GLuint carregaTextura()
{
    char *wa = carrega_bmp();
    GLuint texid;
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, wa);
    free(wa);
    return texid;
}

void colocaImagem()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display(void)
{
    colocaImagem();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // gluLookAt(0.0f, 0.0f, 10.0f,
    //           0.0f, 0.0f, 0.0f,
    //           0.0f, 1.0f, 0.0f);

    // glRotatef(angulo, rotX, rotY, rotZ);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord3f(0, 1, 0);
    glVertex3f(0, 500, 0);
    glTexCoord3f(1, 1, 0);
    glVertex3f(500, 500, 0);
    glTexCoord3f(1, 0, 0);
    glVertex3f(500, 0, 0);
    glEnd(); // angulo += velocidade;

    // glColor3f(1, 0, 0);
    glDisable(GL_TEXTURE_2D);
    // glRecti(250, 250, 250 + 10, 250 + 10);
    drawFood();
    drawCobra();
    // glFlush();
    glutSwapBuffers();
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

// void reshape(int w, int h)
// {
//     // Função é chamada caso a tela tenha sido alterada
//     if (h == 0)
//         h = 1;
//     float proporsao = w * 1.0 / h;
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glViewport(0, 0, w, h);
//     gluPerspective(45.0f, proporsao, 0.1f, 100.0f);
//     glMatrixMode(GL_MODELVIEW);
// }

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

    case ' ':
    {
        if (rotX == 1.0f)
        {
            rotX = 0.0f;
            rotY = 1.0f;
            rotZ = 0.0f;
        }
        else if (rotY == 1.0f)
        {
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 1.0f;
        }
        else if (rotZ == 1.0f)
        {
            rotX = 1.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
        }
    }
    }
}

void special(int key, int x, int y)
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

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            printf("Clicou com o botão esquerdo na Posição  X : %i Y : %i \n", x, y);
        }
        else if (state == GLUT_UP)
        {
            printf("Soltou Botão esquerdo\n");
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            printf("Clicou com o botão direito na Posição  X : %i Y : %i \n", x, y);
        }
        else if (state == GLUT_UP)
        {
            printf("Soltou Botão direito\n");
        }
    }
    else if (button == GLUT_MIDDLE_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            printf("Clicou com o botão do meio na Posição  X : %i Y : %i \n", x, y);
        }
        else if (state == GLUT_UP)
        {
            printf("Soltou Botão do meio\n");
        }
    }
}

void MovimentoMouse(int x, int y)
{
    printf("Mouse na Posição  X : %i Y : %i \n", x, y);
}

void init(void)
{
    glOrtho(0, 500, 0, 500, -1, 1);
    glShadeModel(GL_FLAT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // glutTimerFunc(DELAY, cobraCounter, 1);
}

// void textura()
// {
//     glutMainLoop();
// }

int main(int argc, char **argv)
{

    // for (int i = 0; i < 2499; i++)
    // {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake 2d- André");
    init();

    texid1 = carregaTextura();

    glutDisplayFunc(display);
    // glutIdleFunc(display);
    glutReshapeFunc(reshape);
    // glutMouseFunc(mouse);
    // glutPassiveMotionFunc(MovimentoMouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(DELAY, cobraCounter, 1);

    // printf("%lu   ", sizeof(CobraUnit));

    //   glutDisplayFunc(display);
    //   glutReshapeFunc(reshape);
    // glutKeyboardFunc(keyboard);
    // glutSpecialFunc(SpecialKeys);

    // glutIdleFunc(cobraCounter);
    // glutTimerFunc(DELAY, cobraCounter, 1);

    // glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}