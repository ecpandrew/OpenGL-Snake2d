#include <GL/freeglut.h>
#include <stdio.h>
#include <sstream>
#include </home/andrew/cgraf/p3/irrklang/include/irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
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
static int step = 12;
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

static int poison_x = rand() % 498 + 1;
static int poison_y = rand() % 498 + 1;

static int big_food_x = rand() % 498 + 1;
static int big_food_y = rand() % 498 + 1;

static int LEVEL = 1;
static int DELAY = 40;

static int iCHILD = 10;
static int iWALLS = 15;
static int iPOISON = 20;
static int iSPEED1 = 25;
static int iSPEED2 = 30;
static int iSPEED3 = 35;
static int iINSANE = 40;
static bool MUSIC = true;

int module(int valor);
int module(int valor)
{
    if (valor < 0)
    {
        return -valor;
    }
    else
    {
        return valor;
    }
}

typedef enum
{
    CHILD,
    WALLS,
    POISON,
    SPEED1,
    SPEED2,
    SPEED3,
    INSANE

} Stage;

static Stage STAGE;

char stage[20];

ISoundEngine *engine;

static bool IS_THERE_FOOD = true;
static bool IS_THERE_BIG_FOOD = true;
static bool DIRECTION_CHANGED = false;

static bool LEFT = false;
static bool RIGHT = false;
static bool UP = false;
static bool DOWN = false;

static float r = 1;
static float g = 0;
static float b = 0;

// static CobraUnit head = generateCobraUnit(head_x, head_y);
// static CobraUnit body1 = generateCobraUnit(250 + 10, 250);
// static CobraUnit body2 = generateCobraUnit(250 + 20, 250);
// static CobraUnit body3 = generateCobraUnit(250 + 30, 250);
// static CobraUnit body4 = generateCobraUnit(250 + 40, 250);
// static CobraUnit body5 = generateCobraUnit(250 + 50, 250);
static CobraUnit cobra[2500]; // = {head, body1, body2, body3, body4, body5};

// void mouse(int button, int state, int x, int y);
void desenhaTextoBmp(int x, int y, void *fonte, char *string);

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
    if (LEVEL == 2)
    {
        STAGE = CHILD;
    }
    else if (LEVEL == iWALLS)
    {
        STAGE = WALLS;
    }
    else if (LEVEL == iPOISON)
    {
        STAGE = POISON;
    }
    else if (LEVEL == iSPEED1)
    {
        STAGE = SPEED1;
        DELAY = 35;
    }
    else if (LEVEL == iSPEED2)
    {
        STAGE = SPEED2;
        DELAY = 30;
    }
    else if (LEVEL == iSPEED3)
    {
        STAGE = SPEED3;
        DELAY = 25;
    }
    else if (LEVEL > iINSANE)
    {
        STAGE = INSANE;
        DELAY = 23;
    }
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
    STAGE = CHILD;
    DELAY = 40;
}
void wallColision()
{
    if (head_x >= 500) // direita
    {

        if (LEVEL > iWALLS)
        {
            stopGame();
            printf("wall 1");
        }
        else
        {
            head_x = 0;
        }
    }
    else if (head_x + 10 <= 0) // direita
    {
        if (LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 2");
        }
        else
        {
            head_x = 500;
        }
        // stopGame();
    }

    if (head_y >= 500)
    {
        if (LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 3");
        }
        else
        {
            head_y = 0;
        }
        // stopGame();
    }
    else if (head_y + 10 <= 0)
    {
        if (LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 4");
        }
        else
        {
            head_y = 500 - 10;
        }
        // stopGame();
    }
}

void drawFood()
{

    glColor3f(1, 0, 0);
    glRecti(food_x, food_y, food_x + 10, food_y + 10);
    if (LEVEL >= iPOISON)
    {

        glColor3f(1, 0, 1);
        glRecti(poison_x, poison_y, poison_x + 10, poison_y + 10);
    }
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
        bool collisionY = head_y + size_default >= aux_y &&
                          aux_y + size_default >= head_y;

        if (collisionX && collisionY && i > 2)
        { // colision
            stopGame();
            printf("cobra colision");
        }
    }
}

void foodColision()
{

    if (!IS_THERE_FOOD)
    {
        food_x = rand() % 497;
        food_y = rand() % 497;
        bool t = true;
        while (t)
        {
            poison_x = rand() % 497;
            poison_y = rand() % 497;

            if ((module(head_x - poison_x) > 35 && module(head_y - poison_y) > 35))
            //  && (module(food_x - poison_x) > 10 && module(food_y - poison_y) > 10))
            {
                t = false;
            }
        }

        IS_THERE_FOOD = true;
    }

    bool collisionX = head_x + size_default >= food_x &&
                      food_x + size_default >= head_x;
    // Collision y-axis?
    bool collisionY = head_y + size_default >= food_y &&
                      food_y + size_default >= head_y;

    bool poisonCollisionX = head_x + size_default >= poison_x &&
                            poison_x + size_default >= head_x;
    // Collision y-axis?
    bool poisonCollisionY = head_y + size_default >= poison_y &&
                            poison_y + size_default >= head_y;

    if (collisionX && collisionY)
    { // colision
        printf("\nFOOD ATED\n");
        engine->play2D("bite2.wav"); // play some mp3 file
        addUnitToCobra();
        IS_THERE_FOOD = false;
    }
    if (poisonCollisionX && poisonCollisionY)
    { // colision
        if (LEVEL >= iPOISON)
        {
            stopGame();
            printf("poison colision");
        }
    }
}

void handleColision()
{
    foodColision();
    wallColision();
    cobraColision();
}
void drawCobra()
{

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
        DIRECTION_CHANGED = false;
    }
    else if (RIGHT)
    {
        head_x += step;
        DIRECTION_CHANGED = false;
    }
    else if (UP)
    {
        head_y += step;
        DIRECTION_CHANGED = false;
    }
    else if (DOWN)
    {
        head_y -= step;
        DIRECTION_CHANGED = false;
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

    // String::number("%1", levelString);
    // levelString = (char *)"Level: " + char(LEVEL);

    char str[10];
    sprintf(str, "%d", LEVEL - 1);
    desenhaTextoBmp(10, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Level: ");
    desenhaTextoBmp(85, 530, GLUT_BITMAP_TIMES_ROMAN_24, str);

    desenhaTextoBmp(250, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Stage: ");

    if (LEVEL >= iWALLS)
    {
        glColor3f(0, 0, 1);
        glBegin(GL_LINE_STRIP);
        glVertex2i(1, 1);
        glVertex2i(1, 499);
        glVertex2i(500, 499);
        glVertex2i(500, 1);
        glVertex2i(1, 1);
        glEnd();
    }
    switch (STAGE)
    {
    case CHILD:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"CHILD");
        break;
    case WALLS:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"WALLS");
        break;
    case POISON:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"POISON");
        break;
    case SPEED1:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"SPEED1");
        break;
    case SPEED2:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"SPEED2");
        break;
    case SPEED3:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"SPEED3");
        break;
    case INSANE:
        glColor3f(0, 0, 0);
        desenhaTextoBmp(320, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"INSANE");
        break;

    default:
        break;
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-50.0, 50.0, -50.0, 50.0 , -1.0, 1.0);

    glOrtho(0, 500, 0, 560, -1, 1);
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
    }
}

void special(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_LEFT:
        if (!RIGHT && !DIRECTION_CHANGED)
        {
            LEFT = true;
            RIGHT = false;
            UP = false;
            DOWN = false;
            DIRECTION_CHANGED = true;
        }

        break;

    case GLUT_KEY_RIGHT:
        if (!LEFT && !DIRECTION_CHANGED)
        {
            LEFT = false;
            RIGHT = true;
            UP = false;
            DOWN = false;
            DIRECTION_CHANGED = true;
        }
        break;

    case GLUT_KEY_UP:
        if (!DOWN && !DIRECTION_CHANGED)
        {
            LEFT = false;
            RIGHT = false;
            UP = true;
            DOWN = false;
            DIRECTION_CHANGED = true;
        }
        break;

    case GLUT_KEY_DOWN:
        if (!UP && !DIRECTION_CHANGED)
        {
            LEFT = false;
            RIGHT = false;
            UP = false;
            DOWN = true;
            DIRECTION_CHANGED = true;
        }
        break;
    }
}

void init(void)
{
    glOrtho(0, 500, 0, 500, -1, 1);
    glShadeModel(GL_FLAT);
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 560);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake 2d- André");
    STAGE = WALLS;
    engine = createIrrKlangDevice();

    init();

    texid1 = carregaTextura();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    glutTimerFunc(DELAY, cobraCounter, 1);

    glutMainLoop();
    return 0;
}

void desenhaTextoBmp(int x, int y, void *fonte,

                     char *string)
{
    glRasterPos2f(x, y);
    while (*string)
        glutBitmapCharacter(fonte, *string++);
}