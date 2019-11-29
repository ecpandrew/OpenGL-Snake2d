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

static int size_default = 10;
static int step = 12;
static bool ENDGAME = false;

GLuint texid1;
static GLfloat spin = 0.0;
int w, h, window, fim = 0;

static int head_x = 400;
static int head_y = 400;

static int head_x_BOT = 100;
static int head_y_BOT = 100;

static int food_x = rand() % 498 + 1;
static int food_y = rand() % 498 + 1;

static int poison_x = rand() % 498 + 1;
static int poison_y = rand() % 498 + 1;

static int big_food_x = rand() % 498 + 1;
static int big_food_y = rand() % 498 + 1;

static int STAGE_LEVEL = 1;

static int BOT_LEVEL = 1;
static int COBRA_LEVEL = 1;

static int DELAY = 40;
static int iCHILD = 10;
static int iWALLS = 15;
static int iPOISON = 20;
static int iSPEED1 = 25;
static int iSPEED2 = 30;
static int iSPEED3 = 35;
static int iINSANE = 40;
static bool MUSIC = true;

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
static bool DIRECTION_CHANGED_BOT = false;

static bool LEFT = false;
static bool RIGHT = false;
static bool UP = false;
static bool DOWN = false;

static bool LEFT_BOT = true;
static bool RIGHT_BOT = false;
static bool UP_BOT = false;
static bool DOWN_BOT = false;

static float r = 1;
static float g = 0;
static float b = 0;
static CobraUnit cobra[2500];    // = {head, body1, body2, body3, body4, body5};
static CobraUnit cobraBot[2500]; // = {head, body1, body2, body3, body4, body5};

CobraUnit generateCobraUnit(int x, int y);
void drawCobra();
void drawFood();
void wallColision();
void foodColision();
void cobraColision();
void handleColision();
void stopGame();
void colocaImagem();
GLuint carregaTextura();
char *carrega_bmp();
void desenhaTextoBmp(int x, int y, void *fonte, char *string);
void cobraCounter(int value);
void addUnitToCobra(bool bot);
void keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
int module(int valor);
void botThink();

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

CobraUnit generateCobraUnit(int x, int y)
{
    CobraUnit auxcobra;
    auxcobra.setPosicaoX(x);
    auxcobra.setPosicaoY(y);
    auxcobra.setSize(size_default);
    return auxcobra;
}

void addUnitToCobra(bool bot)
{
    if (bot)
    {
        cobraBot[BOT_LEVEL] = generateCobraUnit(head_x_BOT + 1000, head_y_BOT);
        BOT_LEVEL++;
    }
    else
    {
        cobra[COBRA_LEVEL] = generateCobraUnit(head_x + 1000, head_y);
        COBRA_LEVEL++;
    }
    // LEVEL++;

    if (STAGE_LEVEL == 2)
    {
        STAGE = CHILD;
    }
    else if (STAGE_LEVEL == iWALLS)
    {
        STAGE = WALLS;
    }
    else if (STAGE_LEVEL == iPOISON)
    {
        STAGE = POISON;
    }
    else if (STAGE_LEVEL == iSPEED1)
    {
        STAGE = SPEED1;
        DELAY = 35;
    }
    else if (STAGE_LEVEL == iSPEED2)
    {
        STAGE = SPEED2;
        DELAY = 30;
    }
    else if (STAGE_LEVEL == iSPEED3)
    {
        STAGE = SPEED3;
        DELAY = 25;
    }
    else if (STAGE_LEVEL > iINSANE)
    {
        STAGE = INSANE;
        DELAY = 23;
    }
}

void stopGame()
{
    printf("\n\nGame stopped\n\n");

    LEFT = false;
    RIGHT = false;
    UP = false;
    DOWN = false;
    head_x = 400;
    head_y = 400;
    head_x_BOT = 100;
    head_y_BOT = 100;
    STAGE_LEVEL = 1;
    COBRA_LEVEL = 1;
    BOT_LEVEL = 1;
    STAGE = CHILD;
    DELAY = 40;
}

void wallColision()
{
    if (head_x >= 500) // direita
    {
        if (STAGE_LEVEL > iWALLS)
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
        if (STAGE_LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 2");
        }
        else
        {
            head_x = 500;
        }
    }
    if (head_y >= 500)
    {
        if (STAGE_LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 3");
        }
        else
        {
            head_y = 0;
        }
    }
    else if (head_y + 10 <= 0)
    {
        if (STAGE_LEVEL >= iWALLS)
        {
            stopGame();
            printf("wall 4");
        }
        else
        {
            head_y = 500 - 10;
        }
    }
}

void drawFood()
{
    glColor3f(1, 0, 0);
    glRecti(food_x, food_y, food_x + 10, food_y + 10);
    if (STAGE_LEVEL >= iPOISON)
    {
        glColor3f(1, 0, 1);
        glRecti(poison_x, poison_y, poison_x + 10, poison_y + 10);
    }
}

void cobraColision()
{
    int aux_x, aux_y, i;

    for (i = 1; i < COBRA_LEVEL; i++)
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

    bool collisionX_BOT = head_x_BOT + size_default >= food_x &&
                          food_x + size_default >= head_x_BOT;
    // Collision y-axis?
    bool collisionY_BOT = head_y_BOT + size_default >= food_y &&
                          food_y + size_default >= head_y_BOT;

    bool poisonCollisionX = head_x + size_default >= poison_x &&
                            poison_x + size_default >= head_x;
    // Collision y-axis?
    bool poisonCollisionY = head_y + size_default >= poison_y &&
                            poison_y + size_default >= head_y;

    if (collisionX && collisionY)
    { // colision
        printf("\nFOOD ATED\n");
        engine->play2D("bite2.wav"); // play some mp3 file
        addUnitToCobra(false);
        IS_THERE_FOOD = false;
        STAGE_LEVEL++;
    }
    else if (collisionX_BOT && collisionY_BOT)
    { // colision
        printf("\nFOOD ATED by bot\n");
        engine->play2D("bite2.wav"); // play some mp3 file
        addUnitToCobra(true);
        IS_THERE_FOOD = false;
        STAGE_LEVEL++;
    }

    if (poisonCollisionX && poisonCollisionY)
    { // colision
        if (STAGE_LEVEL >= iPOISON)
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

    for (i = 0; i < COBRA_LEVEL; i++)
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

void drawBot();
void drawBot()
{
    int i, j = 0;

    for (i = 0; i < BOT_LEVEL; i++)
    {

        int x = cobraBot[i].getPosicaoX();
        int y = cobraBot[i].getPosicaoY();

        int s = cobraBot[i].getSize();

        glColor3f(1, 1, 0);

        glRecti(x, y, x + s, y + s);
        // glColor3f(1, 1, 1);e

        // glEnd();

        // glFlush();
    }
}

void cobraCounter(int value)
{
    botThink();
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

    if (UP_BOT)
    {
        head_y_BOT += step;
        DIRECTION_CHANGED_BOT = false;
    }
    else if (DOWN_BOT)
    {
        head_y_BOT -= step;
        DIRECTION_CHANGED_BOT = false;
    }
    else if (LEFT_BOT)
    {
        head_x_BOT -= step;
        DIRECTION_CHANGED_BOT = false;
    }
    else if (RIGHT_BOT)
    {
        head_x_BOT += step;
        DIRECTION_CHANGED_BOT = false;
    }

    if (STAGE_LEVEL == 1)
    {
        addUnitToCobra(false);
        addUnitToCobra(true);
        IS_THERE_FOOD = false;
        STAGE_LEVEL++;
    }
    printf("LEVEL: %i ;Cobra andou  X : %i Y : %i \n", STAGE_LEVEL, head_x_BOT, head_y_BOT);
    handleColision();

    for (int i = COBRA_LEVEL; i > 0; i--)
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

    for (int i = BOT_LEVEL; i > 0; i--)
    {

        if (i == 1)
        {
            cobraBot[0].setPosicaoX(head_x_BOT);
            cobraBot[0].setPosicaoY(head_y_BOT);
        }

        if (i == 0)
        {
            continue;
        }
        else
        {
            int aux_x = cobraBot[i - 1].getPosicaoX();
            int aux_y = cobraBot[i - 1].getPosicaoY();

            cobraBot[i].setPosicaoX(aux_x);
            cobraBot[i].setPosicaoY(aux_y);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(DELAY, cobraCounter, 1);
}

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
    glDisable(GL_TEXTURE_2D);
    drawFood();
    drawCobra();
    drawBot();
    char str[10];
    sprintf(str, "%d", STAGE_LEVEL - 1);
    desenhaTextoBmp(10, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Level: ");
    desenhaTextoBmp(85, 530, GLUT_BITMAP_TIMES_ROMAN_24, str);
    desenhaTextoBmp(250, 530, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Stage: ");
    if (STAGE_LEVEL >= iWALLS)
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
    glOrtho(0, 500, 0, 560, -1, 1);
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
    // engine->play2D("loop.ogg", true);
    engine->play3D("loop.ogg",
                   vec3df(0, 0, 10), true, false, true);
    texid1 = carregaTextura();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    glutTimerFunc(DELAY, cobraCounter, 1);

    glutMainLoop();
    return 0;
}

void desenhaTextoBmp(int x, int y, void *fonte, char *string)
{
    glRasterPos2f(x, y);
    while (*string)
        glutBitmapCharacter(fonte, *string++);
}

void botThink()
{
    int dx = head_x_BOT - food_x;
    int dy = head_y_BOT - food_y;

    bool collisionY = head_y_BOT + size_default >= food_y &&
                      food_y + size_default >= head_y_BOT;

    bool collisionX = head_x_BOT + size_default >= food_x &&
                      food_x + size_default >= head_x_BOT;

    printf("\ny col %s", collisionY ? "true" : "false");
    printf("\nx col %s", collisionX ? "true" : "false");
    printf("\ndy %i", dy);

    if(dy >= 0 && dx <=0 ){

        if(collisionY){
            LEFT_BOT = false;
            RIGHT_BOT = true;
            UP_BOT = false;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }else{
            LEFT_BOT = false;
            RIGHT_BOT = false;
            UP_BOT = false;
            DOWN_BOT = true;
            DIRECTION_CHANGED_BOT = true;
        }
    
    }else if(dy >= 0 && dx >= 0 ){

        if(collisionY){
            LEFT_BOT = true;
            RIGHT_BOT = false;
            UP_BOT = false;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }else{
            LEFT_BOT = false;
            RIGHT_BOT = false;
            UP_BOT = false;
            DOWN_BOT = true;
            DIRECTION_CHANGED_BOT = true;
        }
    
    }if(dy <= 0 && dx <=0 ){

        if(collisionY){
            LEFT_BOT = false;
            RIGHT_BOT = true;
            UP_BOT = false;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }else{
            LEFT_BOT = false;
            RIGHT_BOT = false;
            UP_BOT = true;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }
    
    }if(dy <= 0 && dx >=0 ){

        if(collisionY){
            LEFT_BOT = true;
            RIGHT_BOT = false;
            UP_BOT = false;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }else{
            LEFT_BOT = false;
            RIGHT_BOT = false;
            UP_BOT = true;
            DOWN_BOT = false;
            DIRECTION_CHANGED_BOT = true;
        }
    
    }
    



    // if (dy >= 0)
    // {
    //     if ((collisionY && dx < 0) || (collisionX))
    //     {

    //         LEFT_BOT = false;
    //         RIGHT_BOT = true;
    //         UP_BOT = false;
    //         DOWN_BOT = false;
    //         DIRECTION_CHANGED_BOT = true;
    //     }
    //     else
    //     {
    //         LEFT_BOT = false;
    //         RIGHT_BOT = false;
    //         UP_BOT = false;
    //         DOWN_BOT = true;
    //         DIRECTION_CHANGED_BOT = true;
    //     }
    // }
    // else if (dy < 0)
    // {
    //     if ((collisionY && dx > 0) || (collisionX))
    //     {

    //         LEFT_BOT = true;
    //         RIGHT_BOT = false;
    //         UP_BOT = false;
    //         DOWN_BOT = false;
    //         DIRECTION_CHANGED_BOT = true;
    //     }
    //     else
    //     {
    //         LEFT_BOT = false;
    //         RIGHT_BOT = false;
    //         UP_BOT = true;
    //         DOWN_BOT = false;
    //         DIRECTION_CHANGED_BOT = true;
    //     }
    // }

    // else if (dx < 0 && dy < 0)
    // {
    //     LEFT_BOT = false;
    //     RIGHT_BOT = false;
    //     UP_BOT = true;
    //     DOWN_BOT = false;
    //     DIRECTION_CHANGED_BOT = true;
    // }
    // else if (dx < 0 && dy > 0)
    // {
    //     LEFT_BOT = false;
    //     RIGHT_BOT = false;
    //     UP_BOT = false;
    //     DOWN_BOT = true;
    //     DIRECTION_CHANGED_BOT = true;
    // }
    // else
    // {
    //     LEFT_BOT = true;
    //     RIGHT_BOT = false;
    //     UP_BOT = false;
    //     DOWN_BOT = true;
    //     DIRECTION_CHANGED_BOT = true;
    // }
}