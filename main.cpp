#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
# define PI           3.14159265358979323846
#include<math.h>>
#include<cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "components.h"

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */

GLfloat r = 0.0f;
//GLfloat twicePi = 2.0f * PI;
//int triangleAmount = 35;
GLfloat h = 0.0f;
GLfloat m = 0.0f;
GLfloat s = 0.0f;

GLfloat position = 0.0f;
GLfloat speed = 0.1f;

GLfloat rainPos= -1.0;

GLfloat autoNightTimer = 0.0f;
GLfloat autoNightSpeed = 0.05f;

GLfloat autoRainTimer = 0.0f;
GLfloat autoRainSpeed = 0.05f;

GLfloat cloud_position = -0.20f;
GLfloat cloud_speed = 0.008f;

GLfloat position_car = 0.0f;
GLfloat speed_car = 0.08f;

GLfloat ship_pos = 0.4f;
GLfloat ship_speed = 0.005f;

bool isDay = true;
bool isRainy = false;
bool keymap = false;
bool isFullScreen = false;
bool isAuto = true;
bool rainy= false;
//GLfloat x,y;



void Idle()
{   Sleep(10);
    glutPostRedisplay();//// marks the current window as needing to be redisplayed
}


void update_car(int value) {

    if(position_car >2.0)
        position_car = 0.0f;

    position_car += speed_car;

	glutPostRedisplay();




	glutTimerFunc(100, update_car, 0);
}

GLfloat position2 = 0.0f;
GLfloat speed2 = 0.03f;


void autoView(){
  if(autoNightTimer > 6){
        isDay = !isDay;
        autoNightTimer = 0.0f;
    }
    autoNightTimer += autoNightSpeed;

    if(autoRainTimer > 2){
        isRainy = !isRainy;
        (isRainy) ? PlaySound("assets/rain.wav", NULL, SND_FILENAME|SND_ASYNC|SND_LOOP) : PlaySound(NULL, 0, 0);
        autoRainTimer = 0.0f;
    }
    autoRainTimer +=autoRainSpeed;
}

void update(int value) {

    if(position <-1.0)
    {
        position = 1.0f;
        position -= speed;
    }

    if(rainPos<-1.0)
    {
        rainPos = -1.0;
        rainPos -=1.47;
    }
    if(cloud_position < -1.2)
    cloud_position = 1.2f;
    cloud_position -=cloud_speed;

    if(ship_pos < -1.8)
    ship_pos = 1.2f;
    ship_pos -= ship_speed;

    (isAuto) ? autoView() : blank();

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}




void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void handleMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON){
			speed_car += 0.1f;
			}
			if (button == GLUT_RIGHT_BUTTON)
	{speed_car -= 0.1f;
			}
	glutPostRedisplay();}






void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
    case 't':
        isAuto = false;
        isDay = !isDay;
        break;
    case 's':
        speed_car = 0.0f;
        break;
    case 'x':
        ship_speed = 0.0f;
        break;
     case 'k':
        keymap = !keymap;
        break;
    case 'i':
        speed_car = 0.1f;
        break;
    case 'r':
        isAuto = false;
        isRainy = !isRainy;
        (isRainy) ? PlaySound("assets/rain.wav", NULL, SND_FILENAME|SND_ASYNC|SND_LOOP) : PlaySound(NULL, 0, 0);
        break;

    case 'a':
        isAuto = !isAuto;
        break;

    case 'f':
        isFullScreen = !isFullScreen;
        (isFullScreen) ? glutFullScreen() : glutReshapeWindow(1200, 800);
        break;
    case 'e':
        exit(0);
        break;
        glutPostRedisplay();
    }




}



void SpecialInput(int key, int x, int y){
switch(key)
{
    case GLUT_KEY_UP:
        ship_speed+=.05;
        break;
    case GLUT_KEY_DOWN:
        ship_speed-=.05;
        break;
    case GLUT_KEY_LEFT:
        PlaySound("assets/car_double_horn.wav", NULL, SND_FILENAME|SND_ASYNC);
        break;
    case GLUT_KEY_RIGHT:
        PlaySound("assets/ship.wav", NULL, SND_FILENAME|SND_ASYNC);
        break;

    }

glutPostRedisplay();
}



void rain()
{   glLoadIdentity();

    float x=0.0;
    float y=-1;
    float x1=-0.099;


    glColor3ub(204, 255, 255);
    glPushMatrix();
    glTranslatef(0.0f,rainPos,0.0f);
    glBegin(GL_LINES);


    for(int i=600;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            glVertex2f(x,y);
            glVertex2f(x+0.05,y+0.09);
            x+=float(rand()%5)/10;
        }
        for(int j=0;j<=i;j++)
        {
            glVertex2f(x1,y);
            glVertex2f(x1+0.05,y+0.09);
            x1-=float(rand()%5)/10;
        }
        y+=float(rand()%10)/10;
        x=0.0;
        x1=-0.099;

    }
    glEnd();
    glPopMatrix();
    glutPostRedisplay();
    }


void rainView()
{

    float x=0.0, y = -1.5, x1=-0.099;
    glColor3ub(255,255,255);
    glPushMatrix();
    glTranslatef(0,rainPos,0);
    glBegin(GL_LINES);

    for(int i=600;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            glVertex3f(x,y,0);
            glVertex3f(x+0.05,y+0.09,0);
            x+=float(rand()%5)/10;
           // x-=rand()%1050;
        }
        for(int j=0;j<=i;j++)
        {
            glVertex3f(x1,y,0);
            glVertex3f(x1+0.05,y+0.09,0);
            //x+=rand()%1050;
            x1-=float(rand()%5)/10;
        }
        y+=float(rand()%10)/10;
        //y-=rand()%15;
        x=0.0;
        x1=-0.099;

    }
    glEnd();
    glPopMatrix();
}
void brickAsh(){
    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.75f, 0.0f);
    glVertex2f(-0.75f, 0.05f);
    glVertex2f(-0.7f, 0.05f);
	glVertex2f(-0.7f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.75f, 0.05f);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.75f, 0.0);
    glVertex2f(-0.75f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.0);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.05f);
    glVertex2f(-0.65f, 0.05f);
	glVertex2f(-0.65f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.05f);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.0);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

}

void brickWhite(){
    glBegin(GL_QUADS);
    glColor3ub(231, 231, 231);
	glVertex2f(-0.75f, 0.0f);
    glVertex2f(-0.75f, 0.05f);
    glVertex2f(-0.7f, 0.05f);
	glVertex2f(-0.7f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.75f, 0.05f);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.75f, 0.0);
    glVertex2f(-0.75f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.0);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(231, 231, 231);
	glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.05f);
    glVertex2f(-0.65f, 0.05f);
	glVertex2f(-0.65f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.05f);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.7f, 0.0);
    glVertex2f(-0.7f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

}


void brickAsh_three(){
   	glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.65f, 0.0f);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
	glVertex2f(-0.6f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(165, 177, 176);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
	glVertex2f(-0.55f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.55f, 0.0f);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0);
    glVertex2f(-0.5f, 0.05f);
    glEnd();


}
void brickWhitethree(){
    glBegin(GL_QUADS);
    glColor3ub(231,231,231);
	glVertex2f(-0.65f, 0.0f);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
	glVertex2f(-0.6f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(165, 177, 176);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(231,231,231);
	glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
	glVertex2f(-0.55f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(231,231,231);
	glVertex2f(-0.55f, 0.0f);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0);
    glVertex2f(-0.5f, 0.05f);
    glEnd();


}

void brickColored_White(){
    glBegin(GL_QUADS);
    glColor3ub(231,231,231);
	glVertex2f(-0.65f, 0.0f);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
	glVertex2f(-0.6f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(165, 177, 176);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
	glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
	glVertex2f(-0.55f, 0.0f);
	glEnd();


    glBegin(GL_QUADS);
    glColor3ub(231,231,231);
	glVertex2f(-0.55f, 0.0f);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0);
    glVertex2f(-0.5f, 0.05f);
    glEnd();


}
void brickColored_Ash(){

    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.65f, 0.0f);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
	glVertex2f(-0.6f, 0.0f);
	glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(165, 177, 176);
    glVertex2f(-0.65f, 0.05f);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.65f, 0.0);
    glVertex2f(-0.65f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.6f, 0.0);
    glVertex2f(-0.6f, 0.05f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
	glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.6f, 0.05f);
    glVertex2f(-0.55f, 0.05f);
	glVertex2f(-0.55f, 0.0f);
	glEnd();


    glBegin(GL_QUADS);
    glColor3ub(204, 204, 204);
	glVertex2f(-0.55f, 0.0f);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(175, 177, 176);
    glVertex2f(-0.55f, 0.05f);
    glVertex2f(-0.5f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0);
    glVertex2f(-0.55f, 0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, 0.0);
    glVertex2f(-0.5f, 0.05f);
    glEnd();
}
void pillarleft(){

    brickAsh();

    glTranslatef(0.0f,0.05f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.05f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.1f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.15f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.2f,0.0f);
    brickAsh();
    glLoadIdentity();


     glTranslatef(0.0f,0.25f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.3f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(0.0f,0.35f,0.0f);
    brickAsh();
    glLoadIdentity();



}
void pillarleftwhiteashwhite(){
    brickColored_White();

    glTranslatef(0.0f,0.05f,0.0f);
    brickColored_White();
    glLoadIdentity();


    glTranslatef(0.0f,0.1f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.15f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.2f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.25f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.3f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.35f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.0f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    //ash..//
    glTranslatef(0.15f,0.0,0.0f);
    brickColored_Ash();
    glLoadIdentity();

    glTranslatef(0.15f,0.05f,0.0f);
    brickColored_Ash();
    glLoadIdentity();


    glTranslatef(0.15f,0.1f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.15f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.2f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.25f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.3f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.35f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.15f,0.4f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    //white
    glTranslatef(0.3f,0.0f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.3f,0.05f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.05f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.1f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.15f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.2f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.25f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.3f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.35f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();

}

void pillarmid(){
    glTranslatef(0.45f,0.0,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(0.45f,0.05f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.1f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.15f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.2f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.25f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.3f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.35f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.45f,0.4f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(0.45f,0.45f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    //2whitemid
	glTranslatef(0.7f,0.0,0.0f);
    brickWhite();
    glLoadIdentity();

    glTranslatef(0.7f,0.05f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.1f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.15f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.2f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.25f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.3f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.35f,0.0f);
    brickWhite();
    glLoadIdentity();


    glTranslatef(0.7f,0.4f,0.0f);
    brickWhite();
    glLoadIdentity();

    glTranslatef(0.7f,0.45f,0.0f);
    brickWhite();
    glLoadIdentity();

    //rightsideash3
      glTranslatef(0.7f,0.0,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(0.7f,0.05f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.1f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.15f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.2f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.25f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.3f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.35f,0.0f);
    brickAsh_three();
    glLoadIdentity();


    glTranslatef(0.7f,0.4f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(0.7f,0.45f,0.0f);
    brickAsh_three();
    glLoadIdentity();




}

void pillarRightwhiteashwhite(){
    glTranslatef(0.85f,0.0f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.85f,0.05f,0.0f);
    brickWhitethree();
    glLoadIdentity();



    glTranslatef(0.85f,0.1f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.15f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.2f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.25f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.3f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.35f,0.0f);
    brickWhitethree();
    glLoadIdentity();


//    glTranslatef(0.85f,0.4f,0.0f);
//    brickWhitethree();
//    glLoadIdentity();
//
//
//    glTranslatef(0.85f,0.45f,0.0f);
//    brickWhitethree();
//    glLoadIdentity();
//
//    glTranslatef(0.85f,0.5f,0.0f);
//    brickWhitethree();
//    glLoadIdentity();



    //ash_mid_portion
    glTranslatef(1.0f,0.0,0.0f);
    //brickAsh_three();
    brickColored_Ash();
    glLoadIdentity();

    glTranslatef(1,0.05f,0.0f);
    //brickAsh_three();
    brickColored_Ash();

    glLoadIdentity();

    glTranslatef(1,0.1f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.15f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.2f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.25f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.3f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.35f,0.0f);
    brickAsh_three();
    glLoadIdentity();

    glTranslatef(1,0.4f,0.0f);
    brickAsh_three();
    glLoadIdentity();

//white right portion

    glTranslatef(1.15f,0.0f,0.0f);
    brickColored_White();
    glLoadIdentity();

    glTranslatef(1.15f,0.05f,0.0f);
    glColor3ub(168, 101, 95);
    brickColored_White();
    glLoadIdentity();



    glTranslatef(1.15f,0.1f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(1.15f,0.15f,0.0f);
    brickWhitethree();
    glLoadIdentity();



    glTranslatef(1.15f,0.2f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(1.15f,0.25f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(1.15f,0.3f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(1.15f,0.35f,0.0f);
    brickWhitethree();
    glLoadIdentity();

     glTranslatef(1.15f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();



}

void pillarRight(){

    glTranslatef(1.4f,0,0.0f);
    brickAsh();
    glLoadIdentity();

    glTranslatef(1.4f,0.05f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.05f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.1f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.15f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.2f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.25f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.3f,0.0f);
    brickAsh();
    glLoadIdentity();


    glTranslatef(1.4f,0.35f,0.0f);
    brickAsh();
    glLoadIdentity();



}




void stairs(){
    glBegin(GL_QUADS);
    glColor3ub(179, 166, 150);
    glVertex2f(-1, 0);
    glVertex2f(-1, -0.02f);
    glVertex2f(1, -0.02f);
    glVertex2f(1, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(156, 106, 97);
    glVertex2f(-1.9f, -0.04f);
    glVertex2f(-1.9f, -0.02f);
    glVertex2f(0.9f, -0.02f);
    glVertex2f(0.9f, -0.04f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(179, 166, 150);
    glVertex2f(-0.9f, -0.04f);
    glVertex2f(-0.9f, -0.06f);
    glVertex2f(0.9f, -0.06f);
    glVertex2f(0.9f, -0.04f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(156, 106, 97);
    glVertex2f(-0.9f, -0.08f);
    glVertex2f(-0.9f, -0.06f);
    glVertex2f(0.9f, -0.06f);
    glVertex2f(0.9f, -0.08f);
    glEnd();
}

void tree1(){
 glBegin(GL_QUADS);
    glColor3ub(77, 40, 0);
    glVertex2f(-0.8f,-0.22f);
    glVertex2f(-0.83f,-0.22f);
    glVertex2f(-0.83f,-0.1f);
    glVertex2f(-0.8f,-0.1f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,77,0);
    glVertex2f(-0.87f,-0.1f);
    glVertex2f(-0.75f,-0.1f);
    glVertex2f(-0.81f,-0.0f);
    glEnd();

//
    glBegin(GL_POLYGON);
    glColor3ub(176, 252, 58);
    glVertex2f(-0.87f,-0.07f);
    glVertex2f(-0.75f,-0.07f);
    glVertex2f(-0.81f,0.07f);
    glEnd();

//    glBegin(GL_POLYGON);
//    glColor3ub(3, 192, 74);
//        glColor3ub(2, 137, 16);
//
//    glVertex2f(-0.87f,-0.04f);
//    glVertex2f(-0.75f,-0.04f);
//    glVertex2f(-0.81f,0.07f);
//    glEnd();
//
////    glBegin(GL_POLYGON);
////    glColor3ub(3, 192, 74);
////    glVertex2f(-0.87f,-0.01f);
////    glVertex2f(-0.75f,-0.01f);
////    glVertex2f(-0.81f,0.08f);
////    glEnd();

    }
void trees(){
    glLoadIdentity();
    glTranslatef(0.22,0.0,0);
    treeComponent();
    glLoadIdentity();

    glTranslatef(0.1,0,0);
    treeComponent();
    glLoadIdentity();


    glLoadIdentity();
    glTranslatef(-1.55,0.0,0);
    treeComponent();
    glLoadIdentity();


    glLoadIdentity();
    glTranslatef(-1.66,0.0,0);
    treeComponent();
    glLoadIdentity();


    glTranslatef(0.1,0,0);
    treeComponent();
    glLoadIdentity();



    glTranslatef(-0.05,0,0);
    tree1();
    glLoadIdentity();


    glTranslatef(1.73,0,0);
    tree1();
    glLoadIdentity();
    //tree2




}

void NightSkyJoinedComponent(){
    anyQuad(1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0, 0, 0);
    moonComponent();
    starComponent();
}


void sky()
{
    (isDay) ? sunComponent() : NightSkyJoinedComponent();

//    glBegin(GL_QUADS);
//    glColor3ub(77, 184, 255);
//    glVertex2f(-1.0, 0.0f);
//    glVertex2f(1.0f, 0.0f);
//    glVertex2f(1.0f, 1.0f);
//    glVertex2f(-1.0f, 1.0f);
//    glEnd();
}
void road()
{
    glBegin(GL_QUADS);
    glColor3ub(51, 204, 51);
    glVertex2f(-1.0, -0.0f);
    glVertex2f(-1.0f, -0.08f);
    glVertex2f(-0.9f, -0.08f);
    glVertex2f(-0.9f, -0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(51, 204, 51);
    glVertex2f(1.0, -0.0f);
    glVertex2f(1.0f, -0.08f);
    glVertex2f(0.9f, -0.08f);
    glVertex2f(0.9f, -0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(51, 204, 51);
    glVertex2f(-1.0, -0.2f);
    glVertex2f(-1.0f, -0.08f);
    glVertex2f(1.0f, -0.08f);
    glVertex2f(1.0f, -0.2f);
    glEnd();



      glBegin(GL_QUADS);    //road
      glColor3ub(115, 115, 115);
      glVertex2f(-1.0f, -0.6f);
      glVertex2f(-1.0f, -0.2f);
      glVertex2f(1.0f,- 0.2f);
      glVertex2f(1.0f,- 0.6f);
      glEnd();

      glBegin(GL_QUADS);    //river
      glColor3ub(77, 184, 255);
      glVertex2f(-1.0f, -0.63f);
      glVertex2f(-1.0f, -1.0f);
      glVertex2f(1.0f,- 1.0f);
      glVertex2f(1.0f,- 0.63f);
      glEnd();

        //crossing

//      glBegin(GL_QUADS);
//      glColor3ub(255,255,255);
//      glVertex2f(0.8f, -0.2f);
//      glVertex2f(0.8f, -0.6f);
//      glVertex2f(0.81f,- 0.2f);
//      glVertex2f(0.8f,- 0.6f);
//      glEnd();

      glBegin(GL_QUADS);    //roadborder
      glColor3ub(26, 13, 0);
      glVertex2f(-1.0f, -0.2f);
      glVertex2f(-1.0f, -0.23f);
      glVertex2f(1.0f,- 0.23f);
      glVertex2f(1.0f,- 0.2f);
      glEnd();

      glBegin(GL_QUADS);    //roadborder
      glColor3ub(26, 13, 0);
      glVertex2f(-1.0f, -0.6f);
      glVertex2f(-1.0f, -0.63f);
      glVertex2f(1.0f,- 0.63f);
      glVertex2f(1.0f,- 0.6f);
      glEnd();

      glBegin(GL_QUADS);        //roadline
      glColor3ub(255,255,255);
      glVertex2f(-0.9f, -0.3f);
      glVertex2f(-0.9f, -0.34f);
      glVertex2f(-0.5f,- 0.34f);
      glVertex2f(-0.5f,- 0.3f);
      glEnd();

      glBegin(GL_QUADS);     //roadline
      glColor3ub(255,255,255);
      glVertex2f(-0.3f, -0.54);
      glVertex2f(-0.3f, -0.5f);
      glVertex2f(0.1f,- 0.5f);
      glVertex2f(0.1f,- 0.54f);
      glEnd();

      glBegin(GL_QUADS);       //roadline
      glColor3ub(255,255,255);
      glVertex2f(0.6f, -0.3f);
      glVertex2f(0.6f, -0.34f);
      glVertex2f(0.2f,- 0.34f);
      glVertex2f(0.2f,- 0.3f);
      glEnd();









}
void light(){

    glScalef(0.7f,0.5f,0.0f);
    glTranslatef(0,-0.2f,0);
    glBegin(GL_POLYGON);
    glColor3ub(26,26,26);
    glVertex2f(-0.4f,-0.22f);
    glVertex2f(-0.418f,-0.22f);
    glVertex2f(-0.418f,0.05f);
    glVertex2f(-0.4f,0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.45f,0.05f);
    glVertex2f(-0.38f,0.05f);
    glVertex2f(-0.38f,0.09f);
    glVertex2f(-0.414f,0.15f);
    glVertex2f(-0.45f,0.09f);
    glEnd();


    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-0.45f,0.05f);
    glVertex2f(-0.38f,0.05f);
    glVertex2f(-0.38f,0.05f);
    glVertex2f(-0.38f,0.09f);
    glVertex2f(-0.38f,0.09f);
    glVertex2f(-0.411f,0.15f);
    glVertex2f(-0.411f,0.15f);
    glVertex2f(-0.45f,0.09f);
    glVertex2f(-0.45f,0.09f);
     glVertex2f(-0.45f,0.05f);
    glEnd();


    //light2
    glBegin(GL_POLYGON);
    glColor3ub(26,26,26);
    glVertex2f(0.4f,-0.22f);
    glVertex2f(0.418f,-0.22f);
    glVertex2f(0.418f,0.05f);
    glVertex2f(0.4f,0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(0.45f,0.05f);
    glVertex2f(0.38f,0.05f);
    glVertex2f(0.38f,0.09f);
    glVertex2f(0.414f,0.15f);
    glVertex2f(0.45f,0.09f);
    glEnd();


    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(0.45f,0.05f);
    glVertex2f(0.38f,0.05f);

    glVertex2f(0.38f,0.05f);
    glVertex2f(0.38f,0.09f);

    glVertex2f(0.38f,0.09f);
    glVertex2f(0.411f,0.15f);

    glVertex2f(0.411f,0.15f);
    glVertex2f(0.45f,0.09f);

    glVertex2f(0.45f,0.09f);
     glVertex2f(0.45f,0.05f);
    glEnd();
    glLoadIdentity();

    //light 3 and 4

    glScalef(0.7f,0.5f,0.0f);
    glTranslatef(0.2f,-0.2f,0);
    glBegin(GL_POLYGON);
    glColor3ub(26,26,26);
    glVertex2f(-0.4f,-0.22f);
    glVertex2f(-0.418f,-0.22f);
    glVertex2f(-0.418f,0.05f);
    glVertex2f(-0.4f,0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(-0.45f,0.05f);
    glVertex2f(-0.38f,0.05f);
    glVertex2f(-0.38f,0.09f);
    glVertex2f(-0.414f,0.15f);
    glVertex2f(-0.45f,0.09f);
    glEnd();


    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(-0.45f,0.05f);
    glVertex2f(-0.38f,0.05f);

    glVertex2f(-0.38f,0.05f);
    glVertex2f(-0.38f,0.09f);

    glVertex2f(-0.38f,0.09f);
    glVertex2f(-0.411f,0.15f);

    glVertex2f(-0.411f,0.15f);
    glVertex2f(-0.45f,0.09f);

    glVertex2f(-0.45f,0.09f);
     glVertex2f(-0.45f,0.05f);
    glEnd();

      //light2
      //light2
    glBegin(GL_POLYGON);
    glColor3ub(26,26,26);
    glVertex2f(0.4f,-0.22f);
    glVertex2f(0.418f,-0.22f);
    glVertex2f(0.418f,0.05f);
    glVertex2f(0.4f,0.05f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 204, 102);
    glVertex2f(0.45f,0.05f);
    glVertex2f(0.38f,0.05f);
    glVertex2f(0.38f,0.09f);
    glVertex2f(0.414f,0.15f);
    glVertex2f(0.45f,0.09f);
    glEnd();


    glBegin(GL_LINES);
    glColor3ub(0,0,0);
    glVertex2f(0.45f,0.05f);
    glVertex2f(0.38f,0.05f);

    glVertex2f(0.38f,0.05f);
    glVertex2f(0.38f,0.09f);

    glVertex2f(0.38f,0.09f);
    glVertex2f(0.411f,0.15f);

    glVertex2f(0.411f,0.15f);
    glVertex2f(0.45f,0.09f);

    glVertex2f(0.45f,0.09f);
     glVertex2f(0.45f,0.05f);
    glEnd();
    glLoadIdentity();

}


void car()
{
        glPushMatrix();
        glTranslatef(position_car,0.0f,0.0f);
        glBegin(GL_POLYGON);
        glColor3ub(51, 51, 204);
        glVertex2f(-0.85, -0.5);
        glVertex2f(-0.55, -0.5);
        glVertex2f(-0.55, -0.44);
        glVertex2f(-0.60, -0.44);
        glVertex2f(-0.65, -0.37);
        glVertex2f(-0.75, -0.37);
        glVertex2f(-0.80, -0.37);
        glVertex2f(-0.85, -0.44);
        glVertex2f(-0.85, -0.5);
        glEnd();

        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(position_car, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.61, -0.44);
        glVertex2f(-0.66, -0.36);
        glVertex2f(-0.79, -0.36);
        glVertex2f(-0.84, -0.44);
        glEnd();
        glPopMatrix();

       glColor3f(0.000, 0.545, 0.545);
       glPushMatrix();
    glTranslatef(position_car, 0.0f, 0.0f);
       glBegin(GL_POLYGON);
        glVertex2f(-0.73, -0.44);
        glVertex2f(-0.72, -0.44);
        glVertex2f(-0.72, -0.36);
        glVertex2f(-0.73, -0.36);
    glEnd();
    glPopMatrix();

    glPushMatrix();
   glTranslatef(position_car, 0.0f, 0.0f);
        glTranslatef(-0.80,-0.48,0);
        glScalef(0.6,1,1);
        glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.04;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(position_car, 0.0f, 0.0f);
        glTranslatef(-0.80,-0.48,0);
        glScalef(0.6,1,1);
        glColor3f(1.000, 1.000, 1.000);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.01;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
    glEnd();
    glPopMatrix();

    glPushMatrix();
   glTranslatef(position_car, 0.0f, 0.0f);
        glTranslatef(-0.63,-0.48,0);
        glScalef(0.6,1,1);
        glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.04;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(position_car, 0.0f, 0.0f);
        glTranslatef(-0.63,-0.48,0);
        glScalef(0.6,1,1);
        glColor3f(1.000, 1.000, 1.000);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=0.01;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y );
        }
    glEnd();
    //glPopMatrix();
    glPopMatrix();

}
void cloudView(){
    glPushMatrix();
    glTranslatef(cloud_position,0,0);
    cloudComponent();

    glTranslatef(cloud_position + 0.8f,0,0);
    cloudComponent();

    glTranslatef(cloud_position - 0.4f,0,0);
    cloudComponent();

    glTranslatef(cloud_position + 1.5f,0,0);
    cloudComponent();

    glTranslatef(cloud_position - 1.2f,0,0);
    cloudComponent();

    glTranslatef(cloud_position - 0.9f,0,0);
    cloudComponent();
    glPopMatrix();
}

void initState(){
    glClearColor(0.5f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void circularShapes(){
   //top
    x=0.25f;
    y=0.55f;
    GLfloat radius=0.025f;
    int i;
    glColor3ub(168, 101, 95);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
    //inner
    x=-0.1f;
    y=0.55f;
    radius=0.025f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	//circle left
    x=-0.25f;
    y=0.55f;
    radius=0.025f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
	//inner

	  x=0.1f;
    y=0.55f;
    radius=0.025f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();


}

void shapesTBQ(){

    glBegin(GL_TRIANGLES);
    glColor3ub(156, 106, 97);
    glVertex2f(0.725f, 0.05f);
    glVertex2f(0.675f, 0.05f);
    glVertex2f(0.7f, 0.25f);
    glEnd();

        glBegin(GL_TRIANGLES);
    glColor3ub(156, 106, 97);
    glVertex2f(-0.725f, 0.05f);
    glVertex2f(-0.675f, 0.05f);
    glVertex2f(-0.7f, 0.25f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(168, 101, 95);
    glVertex2f(0.55f, 0.15f);
    glVertex2f(0.6f, 0.15f);
    glVertex2f(0.575f, 0.35f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.55f, 0.15f);
    glVertex2f(-0.6f, 0.15f);
    glVertex2f(-0.575f, 0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(168, 101, 95);
    glVertex2f(0.4f, 0.15f);
    glVertex2f(0.45f, 0.15f);
    glVertex2f(0.425f, 0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.4f, 0.15f);
    glVertex2f(-0.45f, 0.15f);
    glVertex2f(-0.425f, 0.3f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.05f, 0);
    glVertex2f(-0.05f, 0.1f);
    glVertex2f(0.05f, 0.1f);
    glVertex2f(0.05f, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.65f, 0.46f);
    glVertex2f(-0.65f, 0.45f);
    glVertex2f(-0.2f, 0.45f);
    glVertex2f(-0.2f, 0.46f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(0.65f, 0.46f);
    glVertex2f(0.65f, 0.45f);
    glVertex2f(0.2f, 0.45f);
    glVertex2f(0.2f, 0.46f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(0.65f, 0.46f);
    glVertex2f(0.65f, 0.45f);
    glVertex2f(0.2f, 0.45f);
    glVertex2f(0.2f, 0.46f);
    glEnd();
    //MID BORDER
    glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.35f,0.6f);
    glVertex2f(-0.35f,0.61f);
    glVertex2f(0.35f, 0.61f);
    glVertex2f(0.35f, 0.6f);
    glEnd();
    //MID BORDER

     glBegin(GL_QUADS);
    glColor3ub(168, 101, 95);
    glVertex2f(-0.25f,0.68f);
    glVertex2f(-0.25f,0.69f);
    glVertex2f(0.25f, 0.69f);
    glVertex2f(0.25f, 0.68);
    glEnd();



}

upperportion(){
    //left
    glTranslatef(0.3f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.3f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.3f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.3f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    //mid
    glTranslatef(0.45f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.45f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.45f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.45f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();

//MID Top peak only//MID

    glTranslatef(0.4f,0.6f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.55f,0.6f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.7f,0.6f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.9f,0.6f,0.0f);
    brickWhite();
    glLoadIdentity();

    glTranslatef(0.4f,0.63f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.55f,0.63f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.7f,0.63f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.9f,0.63f,0.0f);
    brickWhite();
    glLoadIdentity();

//...finsihed MID Top peak only//MID


    glTranslatef(0.6f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.6f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();



    glTranslatef(0.6f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.6f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.7f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.7f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.7f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.7f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    //right
    glTranslatef(0.85f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.85f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.85f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();

     glTranslatef(0.85f,0.4f,0.0f);
    brickWhitethree();
    glLoadIdentity();
    glTranslatef(0.85f,0.45f,0.0f);
    brickWhitethree();
    glLoadIdentity();

    glTranslatef(0.85f,0.5f,0.0f);
    brickWhitethree();
    glLoadIdentity();


    glTranslatef(0.85f,0.55f,0.0f);
    brickWhitethree();
    glLoadIdentity();




//
}

void boat(){
glBegin(GL_QUADS);
    glColor3ub(41, 34, 31);
    glVertex2f(0.0f, -0.7f);    // x, y
    glVertex2f(0.1f,-0.9f);
    glVertex2f(0.7f, -0.9f);
    glVertex2f(0.8f,-0.7f);    // x, y
	glEnd();

    //blocks
    glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.1f, -0.75f);    // x, y
    glVertex2f(0.1f,-0.81f);
    glVertex2f(0.15f, -0.81f);
    glVertex2f(0.15f,-0.75f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.2f, -0.75f);    // x, y
    glVertex2f(0.2f,-0.81f);
    glVertex2f(0.25f, -0.81f);
    glVertex2f(0.25f,-0.75f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.3f, -0.75f);    // x, y
    glVertex2f(0.3f,-0.81f);
    glVertex2f(0.35f, -0.81f);
    glVertex2f(0.35f,-0.75f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.4f, -0.75f);    // x, y
    glVertex2f(0.4f,-0.81f);
    glVertex2f(0.45f, -0.81f);
    glVertex2f(0.45f,-0.75f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.5f, -0.75f);    // x, y
    glVertex2f(0.5f,-0.81f);
    glVertex2f(0.55f, -0.81f);
    glVertex2f(0.55f,-0.75f);    // x, y
	glEnd();

	 glBegin(GL_QUADS);
    glColor3ub(138, 133, 131);
    glVertex2f(0.6f, -0.75f);    // x, y
    glVertex2f(0.6f,-0.81f);
    glVertex2f(0.65f, -0.81f);
    glVertex2f(0.65f,-0.75f);    // x, y
	glEnd();

    //ship floor
    glBegin(GL_QUADS);
    glColor3ub(179, 179, 179);
    glVertex2f(0.1f, -0.55f);    // x, y
    glVertex2f(0.1f,-0.7f);
    glVertex2f(0.7f, -0.7f);
    glVertex2f(0.7f,-0.55f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(0.15f, -0.65f);    // x, y
    glVertex2f(0.15f,-0.6f);
    glVertex2f(0.35f, -0.6f);
    glVertex2f(0.35f,-0.65f);    // x, y
	glEnd();


	glBegin(GL_LINES);
    glColor3ub(31, 31, 31);
    glVertex2f(0.2f, -0.65f);    // x, y
    glVertex2f(0.2f,-0.6f);
	glEnd();

	glBegin(GL_LINES);
    glColor3ub(31, 31, 31);
    glVertex2f(0.25f, -0.65f);    // x, y
    glVertex2f(0.25,-0.6f);
	glEnd();

	glBegin(GL_LINES);
    glColor3ub(31, 31, 31);
    glVertex2f(0.3f, -0.65f);    // x, y
    glVertex2f(0.3f,-0.6f);
	glEnd();




	glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(0.4f, -0.65f);    // x, y
    glVertex2f(0.4f,-0.6f);
    glVertex2f(0.55f, -0.6f);
    glVertex2f(0.55,-0.65f);    // x, y
	glEnd();


    glBegin(GL_LINES);
    glColor3ub(31, 31, 31);
    glVertex2f(0.45f, -0.65f);    // x, y
    glVertex2f(0.45f,-0.6f);
	glEnd();

	glBegin(GL_LINES);
    glColor3ub(31, 31, 31);
    glVertex2f(0.5f, -0.65f);    // x, y
    glVertex2f(0.5f,-0.6f);
	glEnd();


    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2f(0.6f, -0.65f);    // x, y
    glVertex2f(0.6f,-0.6f);
    glVertex2f(0.65f, -0.6f);
    glVertex2f(0.65,-0.65f);    // x, y
	glEnd();

//chimneys
  glBegin(GL_QUADS);
    glColor3ub(43, 40, 40);
    glVertex2f(0.2f, -0.3f);    // x, y
    glVertex2f(0.2f,-0.55f);
    glVertex2f(0.25f, -0.55f);
    glVertex2f(0.25f,-0.3f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 70, 0);
    glVertex2f(0.21f, -0.25f);    // x, y
    glVertex2f(0.2f,-0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.24f,-0.25f);    // x, y
	glEnd();

    glTranslatef(0.1f,0.0f,0.0f);
    glBegin(GL_QUADS);
	glColor3ub(43, 40, 40);
    glVertex2f(0.2f, -0.3f);    // x, y
    glVertex2f(0.2f,-0.55f);
    glVertex2f(0.25f, -0.55f);
    glVertex2f(0.25f,-0.3f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 70, 0);
    glVertex2f(0.21f, -0.25f);    // x, y
    glVertex2f(0.2f,-0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.24f,-0.25f);    // x, y
	glEnd();

    glTranslatef(0.1f,0.0f,0.0f);
    glBegin(GL_QUADS);
	glColor3ub(43, 40, 40);
    glVertex2f(0.2f, -0.3f);    // x, y
    glVertex2f(0.2f,-0.55f);
    glVertex2f(0.25f, -0.55f);
    glVertex2f(0.25f,-0.3f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 70, 0);
    glVertex2f(0.21f, -0.25f);    // x, y
    glVertex2f(0.2f,-0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.24f,-0.25f);    // x, y
	glEnd();

    glTranslatef(0.1f,0.0f,0.0f);

    glBegin(GL_QUADS);
	glColor3ub(43, 40, 40);
    glVertex2f(0.2f, -0.3f);    // x, y
    glVertex2f(0.2f,-0.55f);
    glVertex2f(0.25f, -0.55f);
    glVertex2f(0.25f,-0.3f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 70, 0);
    glVertex2f(0.21f, -0.25f);    // x, y
    glVertex2f(0.2f,-0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.24f,-0.25f);    // x, y
	glEnd();

	glTranslatef(0.1f,0.0f,0.0f);

    glBegin(GL_QUADS);
	glColor3ub(43, 40, 40);
    glVertex2f(0.2f, -0.3f);    // x, y
    glVertex2f(0.2f,-0.55f);
    glVertex2f(0.25f, -0.55f);
    glVertex2f(0.25f,-0.3f);    // x, y
	glEnd();

    glBegin(GL_QUADS);
    glColor3ub(235, 70, 0);
    glVertex2f(0.21f, -0.25f);    // x, y
    glVertex2f(0.2f,-0.3f);
    glVertex2f(0.25f, -0.3f);
    glVertex2f(0.24f,-0.25f);    // x, y
	glEnd();
	glLoadIdentity();

}
void boatsmall(){
    glTranslatef(0,-0.3f,0);
    glPushMatrix();
    glTranslatef(ship_pos,0.0f,0);

    //glTranslatef(0.4f,-0.3f,0.0f);
    glScalef(0.7f,0.7f,0.0f);
    boat();
    glPopMatrix();

    glLoadIdentity();


}
void house(){
    pillarleft();
    pillarleftwhiteashwhite();
    pillarRightwhiteashwhite();
    pillarRight();
    upperportion();
    pillarmid();
    shapesTBQ();
    circularShapes();
    stairs();

    Sleep(12);

}
void keymappings(){
    //anyText("x = stop ship , s = stop car , key up = increase ship speed , key down = decrease ship speed , key left = car horn , key right = ship horn", -0.95f, -0.90f, 255, 255, 255);
    anyText("t = toggle daynight , a = auto on \\ off , r = toggle rain , k = keymap show , f = toggle fullscreen , e = exit", -0.95f, -.95f, 255, 255, 255);

    anyText("s = stop car,  key left = car horn, left mouse button= car speed +, right mouse= car speed -", -0.95f, -0.90f, 255, 255, 255);
    anyText("x = stop ship,  key right = ship horn, up= ship speed +, down = ship speed -", -0.95f, -0.85f, 255, 255, 255);
}

void display() {

    glClearColor(0.48, 0.99, 1.00, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);

    init();

    sky();
    (isRainy) ? cloudView() : blank();

    house();
    road();
    car();

    (keymap) ? blank() : keymappings();

    boatsmall();
    trees();
    light();
    (isRainy) ? rainView() : blank();

    glFlush();


}




/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("Parliament House"); // Create a window with the given title
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutReshapeWindow(640, 640);
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutIdleFunc(Idle);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutTimerFunc(1500, update, 0);

    glutTimerFunc(100, update_car, 0);
	glutMainLoop();           // Enter the event-processing loop
	return 0;

}
