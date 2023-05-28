#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;
#define PI 3.1415926
int frameNumber = 0;
GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;
double ok = 1;
int vieti = 3;
double j = 0.0;
double i = 0.0;
double contor = 0;
double loc_vert = 800;
double loc_politie = 800;
int vector[4] = { 0, 117, 235, 352 };
double height;
int scor = 0;
double timp = 0.25;
int pct = 1000;
int noapte;
double rotate_wheel_right = 0.0;
double rotate_wheel_left = 0.0;
float text_scale = 1.0f;
float text_apha = 0.001;
int restart = 0;

void init(void)
{
    glClearColor(0.98, 0.929, 0.792, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void drawDisk(double radius) {
    int d;
    glBegin(GL_POLYGON);
    for (d = 0; d < 32; d++) {
        double angle = 2 * PI / 32 * d;
        glVertex2d(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawWheel(int rotation_direction) {
    glColor3f(0, 0, 0);
    drawDisk(20); // marginea neagra

    glColor3f(0.75f, 0.75f, 0.75f);
    drawDisk(16); //discul gri

    glColor3f(0, 0, 0);
    glPushMatrix();
    if (rotation_direction == 1)
        glRotatef(rotate_wheel_right = rotate_wheel_right - 0.08, 0, 0, 1);
    else
        glRotatef(rotate_wheel_left = rotate_wheel_left + 0.08, 0, 0, 1);
    glRecti(-5, -5, 5, 5);//janta
    glPopMatrix();

    glEnd();
}

void drawCar(int poz, bool police)
{
    if (police == 1)
        glColor3f(0, 0, 0);
    glRecti(-70, -15, 70, 15); // baza masinii

    if (police == 1)
        glColor3f(1, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // jumatatea de sus a masinii
    glBegin(GL_POLYGON);
    glVertex2s(-45, 15);
    glVertex2s(-25, 40);
    glVertex2s(25, 40);
    glVertex2s(45, 15);
    glEnd();

    if (police == 1)
    {
        glColor3f(0, 0, 1); //girofar
        glRecti(-10, 40, 0, 45);

        glColor3f(1, 0, 0);
        glRecti(0, 40, 10, 45);

        glColor3f(1, 1, 1); // usi albe
        glRecti(-45, -15, 45, 15);
    }

    // geam spate
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.7, 0.8); //bleu
    glVertex2s(-38, 17);
    glVertex2s(-22, 37);
    glVertex2s(-2, 37);
    glVertex2s(-2, 17);
    glEnd();

    //geam fata
    glBegin(GL_POLYGON);
    glVertex2s(2, 17);
    glVertex2s(2, 37);
    glVertex2s(22, 37);
    glVertex2s(38, 17);
    glEnd();


    glColor3f(0, 0, 0); //negru
    if (poz == 1) { // masina are fata spre dreapta
        //maner spate
        glPushMatrix();
        glTranslatef(-35, 10, 0);
        glRecti(0, 0, 5, 2);
        glPopMatrix();

        //maner fata
        glPushMatrix();
        glTranslatef(5, 10, 0);
        glRecti(0, 0, 5, 2);
        glPopMatrix();
    }
    else { // masina are fata spre stanga
        //maner spate
        glPushMatrix();
        glTranslatef(-5, 10, 0);
        glRecti(0, 0, 5, 2);
        glPopMatrix();

        //maner fata
        glPushMatrix();
        glTranslatef(35, 10, 0);
        glRecti(0, 0, 5, 2);
        glPopMatrix();
    }



    glPushMatrix();
    glTranslatef(-40, -16, 0);
    if (poz == 1)
        drawWheel(1); // roata spate
    else
        drawWheel(2);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(40, -16, 0);
    if (poz == 1)
        drawWheel(1); // roata fata
    else
        drawWheel(2);
    glPopMatrix();

    glEnd();
}

void heart(int x, int y)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2s(x + 20, y);
    glVertex2s(x + 28, y + 12);
    glVertex2s(x + 32, y + 20);
    glVertex2s(x + 32, y + 24);
    glVertex2s(x + 28, y + 28);
    glVertex2s(x + 24, y + 28);
    glVertex2s(x + 20, y + 24);
    glVertex2s(x + 16, y + 28);
    glVertex2s(x + 12, y + 28);
    glVertex2s(x + 8, y + 24);
    glVertex2s(x + 8, y + 20);
    glVertex2s(x + 12, y + 12);
    glEnd();
}

void draw_hearts()
{
    if (vieti == 1)
    {
        heart(-90, 410);
    }
    else if (vieti == 2)
    {
        heart(-90, 410);
        heart(-50, 410);
    }
    else if (vieti == 3)
    {
        heart(-90, 410);
        heart(-50, 410);
        heart(-10, 410);
    }
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    glutBitmapString(font, string);
}

void startgame(void)
{
    if (height != j || (loc_vert > 130 || loc_vert < -130)) // daca cele 2 masini sunt pe verticale diferite
        //sau daca masinile nu se ating
    {
        loc_vert -= timp;

        if (loc_vert < -130) { // daca masina e in afara ecranului, in stanga
            if (ok == 1) //daca a ajuns singura acolo
            {
                if (timp < 0.8) //setam un maxim pt viteza cu care merge adversarul
                    timp += 0.03;
                scor += 100;
            }
            else { //daca am fc accident si am mutat-o noi in stanga
                ok = 1;
            }

            height = vector[rand() % 4]; //reset
            loc_vert = 800;
        }
        glutPostRedisplay();
    }
    else {
        if (ok == 1) { // pt a scadea viata doar o data
            vieti = vieti - 1;
            if (vieti != 0)
                loc_vert = -160; //resetam masina oponentului doar daca nu am pierdut inca
            ok = 0;
        }
    }
}

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (restart == 2)
    {
        restart = 0;
        vieti = 3;
        loc_vert = 800;
        loc_politie = 800;
        j = 0;
        i = 0;
        scor = 0;
        pct = 1000;
        timp = 0.15;
        ok = 1;
        contor = 0;
        height = vector[rand() % 4];
    }

    if (noapte == 0)
        glColor3f(0.55, 0.788, 0.451);
    else
        if (noapte == 1)
            glColor3f(0, 0, 0);



    // Iarba de jos
    glBegin(GL_POLYGON);
    glVertex2i(-100, -140);// Stanga jos
    glVertex2i(700, -140); // Dreapta jos
    glVertex2i(700, -80);  // Dreapta sus
    glVertex2i(-100, -80); // Stanga sus
    glEnd();

    // Iarba de sus
    glBegin(GL_POLYGON);
    glVertex2i(-100, 400);// Stanga jos
    glVertex2i(700, 400); // Dreapta jos
    glVertex2i(700, 460); // Dreapta sus
    glVertex2i(-100, 460);// Stanga sus
    glEnd();


    if (text_scale <= 1)
        text_apha = 0.005;
    else if (text_scale >= 5)
        text_apha = -0.005;
    glPushMatrix();
    text_scale += text_apha;
    glTranslated(200, 425, 0);
    glScalef(text_scale, text_scale, 1.0);
    glTranslated(-200, -425, 0);
    RenderString(200, 425, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Depaseste masinile!");
    glPopMatrix();

    //vietile
    draw_hearts();

    //afisare scor
    string text = "Scor: ";
    text = text + to_string(scor);
    for (int i = 0; i < text.size(); i++) {
        glRasterPos2i(500 + i * (15), 425);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glPopMatrix();


    // Delimitare sosea
    glLineWidth(3);
    glColor3f(1, 1, 1);

    // Delimitam soseaua de iarba partea de jos
    glBegin(GL_LINES);
    glVertex2i(-100, -80);
    glVertex2i(1500, -80);

    // Delimitam soseaua de iarba partea de sus
    glVertex2i(-100, 400);
    glVertex2i(1500, 400);

    // Liniile intrerupte
   /* glPushMatrix();
    glTranslated(i, 0.0, 0.0);*/

    //linia dubla continua
    glVertex2i(-100, 155);
    glVertex2i(1500, 155);
    glVertex2i(-100, 165);
    glVertex2i(1500, 165);
    glEnd();

    //cele 2 linii punctate
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(10, 0xAAAA);
    glBegin(GL_LINES);
    glVertex2i(-100, 37.5); //linia de jos
    glVertex2i(1500, 37.5);

    glVertex2i(-100, 282.5); //linia de sus
    glVertex2i(1500, 282.5);
    glEnd();
    glDisable(GL_LINE_STIPPLE);



    //desenam masina cu care jucam
    glColor3f(0.996, 0.365, 0.149); //portocaliu
    glPushMatrix();
    glTranslated(0.0, j - 20, 0.0); // putin mai jos
    drawCar(1, 0);
    glPopMatrix();
    glEnd();


    if (vieti == 0) {
        RenderString(250, 155, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
        if (loc_politie > loc_vert + 150 && loc_politie > 150)
            loc_politie -= 0.2;

        glPushMatrix();
        glTranslated(loc_politie, height - 20, 0.0); // putin mai jos
        drawCar(2, 1); //masina de politie
        glPopMatrix();
        glEnd();

    }

    if (contor == 1 && (j != 117 && j != 235 && j != 352))
        j = j + 1;
    else if (contor == -1 && (j != 0 && j != 117 && j != 235))
        j = j - 1;
    else {
        contor = 0;

    }

    //desenam a doua masina (adversara)
    glColor3f(0.471, 0.667, 0.949);
    glPushMatrix();
    glTranslated(loc_vert, height - 20, 0.0); // putin mai jos
    drawCar(2, 0);
    glPopMatrix();
    glEnd();
    if (vieti != 0)
        startgame();
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        if (vieti != 0) {
            if (j < 350) {
                contor = 1;
                j += 1;
            }
            glutPostRedisplay();
        }
        break;
    case GLUT_KEY_DOWN:
        if (vieti != 0) {
            if (j > 0) {
                contor = -1;
                j -= 1;
            }
            glutPostRedisplay();
        }
        break;
    }
}

void callback_Color(int key)
{
    if (key != 2)
        noapte = key;
    else
        restart = key;
}

int main(int argc, char** argv)
{
    int menuBackground;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Racing");
    init();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    menuBackground = glutCreateMenu(callback_Color);
    glutAddMenuEntry("Zi ", 0);
    glutAddMenuEntry("Noapte ", 1);
    glutAddMenuEntry("Restart ", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}