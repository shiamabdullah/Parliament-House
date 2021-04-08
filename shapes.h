#include <iostream>
#include <GL/glut.h>
#include <cmath>
#define PI  3.14159265358979323846
using namespace std;

int i;
int triangleAmount = 500;
GLfloat x = 0,y = 0,radius = 0;
GLfloat twicePi = 2.0f * PI;

void Circle(GLfloat cx, GLfloat cy, GLfloat radius, int r, int g, int b)
{
    glColor3ub(r,g,b);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx, cy);
		for(int i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            cx + (radius * cos(i *  twicePi / triangleAmount)),
			    cy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}


void anyTriangle( float a, float b, float c, float d, float e, float f, int R, int G, int B ){
    glBegin(GL_TRIANGLES);
    glColor3ub(R, G, B);
    glVertex2f(a, b);
    glVertex2f(c, d);
    glVertex2f(e, f);
    glEnd();
}

void anyQuad( float a, float b, float c, float d, float e, float f, float g, float h, int R, int G, int B ){
    glBegin(GL_QUADS);
    glColor3ub(R, G, B);
    glVertex2f(a, b);
    glVertex2f(c, d);
    glVertex2f(e, f);
    glVertex2f(g, h);
    glEnd();
}

void lineComponent(float a, float b, float c, float d){
   glBegin(GL_LINES);
   glVertex2f(a, b);
   glVertex2f(c, d);
   glEnd();
}

void anyText(string text, float x, float y, int R, int G, int B){
    glColor3ub(R, G, B);
    glRasterPos2f(x, y);
    for (i = 0; i < text.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}