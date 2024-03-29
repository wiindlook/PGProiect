/*
 * doll.c
 *
 */

#include <stdio.h>
#include <gl/freeglut.h>                  //GLUT toolkit
#include <time.h>
#define INIT_VIEW_X 0.0    // Definim pozitia initiala a camerei si a modul de vizualizare a ferestrei
#define INIT_VIEW_Y 0.0
#define INIT_VIEW_Z -4.5
#define VIEW_LEFT -2.0
#define VIEW_RIGHT 2.0
#define VIEW_BOTTOM -2.0
#define VIEW_TOP 2.0
#define VIEW_NEAR 1.0
#define VIEW_FAR 200.0
GLfloat AmbientLight[] = { 0.3,0.3,0.3,1.0 };                  //Initializam valorile pentru efectul de lighting
GLfloat DiffuseLight[] = { 0.8,0.8,0.8,1.0 };
GLfloat SpecularLight[] = { 1.0,1.0,1.0,1.0 };
GLfloat SpecRef[] = { 0.7,0.7,0.7,1.0 };
GLfloat LightPos[] = { -50.0,50.0,100.0,1.0 };
GLint Shine = 128;
GLint walkX = 0, walkY = 0, lookX = 0, lookY = 0;
GLint world = 1, oldX = -1, oldY = -1;
GLint model = -1;

void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.17, 1.1, .75);     //Coordonatele ochiului drept
    glRotatef(-45, 0, 0, 1);
    glScalef(.9, .7, .7);            //Marimea ochiului drept
    glColor3f(1.0, 1.0, 1.0);       //Culoarea ochiului drept
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17, 1.1, .75);     //Pozitia ochiului stang
    glRotatef(45, 0, 0, 1);
    glScalef(.9, .7, .7);
    glColor3f(1.0, 1.0, 1.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void legleft()
{
    glPushMatrix();
    glTranslatef(.3, -.5, 0);     //Pozitia piciorului stang
    glRotatef(-90.0, 1, 0, 0);
    glScalef(.8, .8, .8);
    gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
    glPopMatrix();
}

void legright()
{
    glPushMatrix();
    glTranslatef(-.3, -.5, 0);     //Pozitia piciorului drept
    glRotatef(-90.0, 1, 0, 0);
    glScalef(.8, .8, .8);
    gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
    glPopMatrix();
}

void armleft()
{
    glPushMatrix();
    glTranslatef(-.82, 0, .1);     //Pozitia bratului stang
    glRotatef(90, 0, 1, 0);
    glRotatef(-50, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
    glPopMatrix();
}

void armright()
{
    glPushMatrix();
    glTranslatef(.82, 0, .1);      //Pozitia bratului drept
    glRotatef(90, 0, 1, 0);
    glRotatef(-130, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
    glPopMatrix();
}

void handleft()
{
    glPushMatrix();
    glTranslatef(.82, 0, .1);     //Pozitia mainii stangi
    glScalef(.4, .3, .3);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}
void handright()
{
    glPushMatrix();
    glTranslatef(-.82, 0, .1);    //Pozitia mainii drepte
    glScalef(.4, .3, .3);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0, .78, .74);
    glScalef(.4, .4, .1);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}

void teeth()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-.08, .72, .76);
    glTranslatef(.055, 0, .005);
    glutSolidCube(.035);
    glTranslatef(.055, 0, 0);
    glutSolidCube(.035);
    glPopMatrix();
}
void eyebrowleft()
{
    glPushMatrix();
    glTranslatef(-.3, 1.5, .97);;
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
    glPopMatrix();
}

void eyebrowright()
{
    glPushMatrix();
    glTranslatef(.3, 1.5, .97);
    glRotatef(270, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
    glPopMatrix();
}

void neckring()
{
    glPushMatrix();
    glTranslatef(0, .5, 0);
    glScalef(.59, .59, .59);
    glRotatef(90.0, 1, 0, 0);
    glutSolidTorus(.1, 1.0, 20, 20);
    glPopMatrix();
}


void head()
{
    glPushMatrix();
    glTranslatef(0, 1.2, 0);
    glScalef(.9, .9, .9);
    glColor3f(1.0, 0.8, 0.6);
    gluSphere(gluNewQuadric(), 1, 100, 100);
    glPopMatrix();
}

void maintopball()
{
    glPushMatrix();
    glTranslatef(0, 2.2, 0);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .18, 100, 100);
    glPopMatrix();
}

void hatring()
{
    glPushMatrix();
    glTranslatef(0, 1.4, 0);
    glScalef(.84, .84, .84);
    glRotatef(90.0, 1, 0, 0);
    glutSolidTorus(.1, 1.0, 20, 20);
    glPopMatrix();
}

void footleft()
{
    glPushMatrix();
    glTranslatef(-.3, -.5, 0);
    glScalef(1.5, .3, 1.5);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void footright()
{
    glPushMatrix();
    glTranslatef(.3, -.5, 0);
    glScalef(1.5, .3, 1.5);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0, -.2, 0);
    glScalef(1, .7, 1);
    glRotatef(90.0, 1, 0, 0);
    gluDisk(gluNewQuadric(), 0, .8, 30, 30);
    glPopMatrix();
}

void BellyCoat()
{
    glPushMatrix();
    glTranslatef(0, .5, 0);
    glScalef(1, .7, 1);
    glRotatef(90.0, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .6, .8, 1, 100, 100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17, 1.1, .88);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .1, 100, 100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.17, 1.1, .88);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .1, 100, 100);
    glPopMatrix();
}

void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1, .4, .85);
    glScalef(1.9, 1.9, 1.9);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}
void middlebutton()
{
    glPushMatrix();
    glTranslatef(-.1, .15, .98);
    glScalef(1.9, 1.9, 1.9);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}
void bottombutton()
{
    glPushMatrix();
    glTranslatef(-.1, -.1, .92);
    glScalef(1.9, 1.9, 1.9);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Goleste fereastra
    glColor3ub(50, 50, 150);//Culoarea background-ului
    glPushMatrix();//Salveaza starea vizualizarii matricii
    if (world == 1)
    {
        glTranslatef(walkX, -1, walkY);
        glRotatef(lookY, 0, 1, 0);
        glRotatef(lookX, 1, 0, 0);
    }


    //*******************Model***********************
    glPushMatrix();
    glTranslatef(-1, 0, -6);



    if (model == 1)
    {
        glTranslatef(walkX, -1, walkY);
        glRotatef(lookY, 0, 1, 0);
        glRotatef(lookX, 1, 0, 0);
    }
    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
    glColor3f(0.0, 1.0, 0.0);
    neckring();
    glColor3ub(50, 40, 60);
    legright();
    legleft();
    glColor3ub(143, 59, 93);
    armleft();
    armright();
    BellyCoat();
    bellyCoatbottom();
    glColor3ub(0, 185, 0);
    handleft();
    handright();
    mouth();
    teeth();
    glColor3ub(255, 222, 173);
    head();
    glColor3f(0.0, 0.0, 0.0);
    footleft();
    footright();
    topbutton();
    middlebutton();
    bottombutton();
    pupilleft();
    pupilright();
    glPopMatrix();

    glPopMatrix();                                     //****Restaureaza starea matricei****
    glutSwapBuffers();                             //****Ia culorile de desenare****
}



void SetupRend()
{
    glClearColor(0.7, 0.7, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);         //Porneste testarea in adancime
    glEnable(GL_LIGHTING);             //Porneste efectul de lighting
    glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);//Seteaza si porneste lumina
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);                   //Porneste urmarirea culorilor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
    glMateriali(GL_FRONT, GL_SHININESS, Shine);//
}

void walk(int key, int x, int y)                                      //schimba pozitia folosing sagetile
{
    if (key == GLUT_KEY_UP)    walkY += 1;
    if (key == GLUT_KEY_DOWN)  walkY -= 1;
    if (key == GLUT_KEY_RIGHT) walkX += 1;
    if (key == GLUT_KEY_LEFT)  walkX -= 1;
    if (key == GLUT_KEY_F10)    world = -world;
    if (key == GLUT_KEY_F9)    model = -model;

}

void gaze(int x, int y)
{
    if ((oldX < 0) || (oldY < 0))
    {

        oldX = x;
        oldY = y;
    }
    lookX += y - oldY;lookY += x - oldX;oldX = x;oldY = y;
}

void myReshape(int w, int h)
{
    GLfloat Ratio;
    glViewport(0, 0, w, h);
    Ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, Ratio, VIEW_NEAR, VIEW_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(INIT_VIEW_X, INIT_VIEW_Y, INIT_VIEW_Z);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Model Preview");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutSpecialFunc(walk);
    glutPassiveMotionFunc(gaze);
    SetupRend();
    glEnable(GL_NORMALIZE);
    glutMainLoop();
}
