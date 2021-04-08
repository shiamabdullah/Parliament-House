#include <windows.h>
#include<mmsystem.h>
#include "components.h"

bool isAuto= true;
bool isDay = true;

GLfloat autoNightTimer = 0.0f;
GLfloat autoNightSpeed = 0.05f;


void autoView(){
  if(autoNightTimer > 5){
        isDay = !isDay;
        autoNightTimer = 0.0f;
    }
    autoNightTimer += autoNightSpeed;
}



void update(int a){
    (isAuto)?autoView():blank();
    glutPostRedisplay();
	glutTimerFunc(100, update, 0);
}


void Idle()
{
    glutPostRedisplay();
    Sleep(10);
}




void skyView(){
    (isDay)?    sunComponent(): moonComponent();
}

void grassView(){
    treeComponent();
    glLoadIdentity();
    glTranslatef(0.2f, 0.2f, 0);
    treeComponent();
    glLoadIdentity();

    glLoadIdentity();
    glTranslatef(0.25f, 0.1f, 0);
    treeComponent();
    glLoadIdentity();
}


void initState(){
    glClearColor(0.5f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);
    glLineWidth(4);
    glPointSize(7);
}

void axisDraw(){
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0, -1.0f);
    glEnd();
}



void fullView(){
    initState();
    axisDraw();
    skyView();
    grassView();
    anyText("Created by: @tamzid, @shohan, @torab, @tarek", 0.2f, -0.17f, 103, 72, 70);





    glFlush();

}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key)
	{
        case 'd':
            isDay = !isDay;
            break;
        case 'a':
            isAuto = !isAuto;
            break;
        glutPostRedisplay();
	}
}


int main(int argc, char** argv) {
    //FreeConsole();
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Ahsan Monjil");
    glutDisplayFunc(fullView);
    glutIdleFunc(Idle);
    glutKeyboardFunc(handleKeypress);
    //glutMouseFunc(handleMouse);
    //glutSpecialFunc(SpecialInput);
    glutTimerFunc(1500, update, 0);
    glutMainLoop();
    return 0;
}
