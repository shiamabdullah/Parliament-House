#include "shapes.h"

void blank(){
}

void sunComponent()
{
    Circle(0.8f, 0.8f, 0.08f, 255, 255, 0);
}


void moonComponent()
{
    Circle(0.8f, 0.8f,  0.08f, 245, 245, 245);
}
void starComponent(){
    glPointSize(4);
    glBegin(GL_POINTS);
	glColor3ub(255,255,255);
	glVertex2f(-0.9,0.9);
	glVertex2f(-0.8,0.8);
	glVertex2f(-0.85,0.55);
    glVertex2f(-0.75,0.65);
    glVertex2f(-0.55,0.85);
    glVertex2f(-0.55,0.85);
    glVertex2f(-0.85,0.75);
    glVertex2f(-0.35,0.75);
    glVertex2f(-0.95,0.45);
    glVertex2f(-0.85,0.65);
    glVertex2f(-0.65,0.55);
    glVertex2f(-0.35,0.64);

    glVertex2f(-0.75,0.75);
    glVertex2f(-0.15,0.75);
    glVertex2f(-0.25,0.75);

    glVertex2f(-0.0,0.75);
    glVertex2f(0.25,0.85);
    glVertex2f(0.275,0.75);
    glVertex2f(0.0,0.75);
    glVertex2f(0.9,0.91);
	glVertex2f(0.875,0.95);
    glVertex2f(0,0.99);
    glVertex2f(-0.1,0.95);
    glVertex2f(-0.2,0.93);
    glVertex2f(-0.4,0.95);
    glVertex2f(0.1,0.95);
    glVertex2f(0.2,0.93);
    glVertex2f(0.4,0.95);
    glVertex2f(0.7,0.95);
    glVertex2f(0.8,0.95);
    glVertex2f(0.1,0.55);
    glVertex2f(0.2,0.63);
    glVertex2f(0.66,0.45);
    glVertex2f(0.8,0.55);
    glVertex2f(0.76,0.35);
    glVertex2f(0.8,0.65);
    glVertex2f(0.6,0.75);
    glVertex2f(0.8,0.55);
    glEnd();
    glPointSize(7);
}


void treeComponent(){
    anyQuad(0.69f, 0.13f, 0.67f, 0.10f, 0.78f, 0.10f, 0.76f, 0.13f, 0, 102, 51);
    anyQuad(0.70f, 0.16f, 0.68f, 0.13f, 0.77f, 0.13f, 0.75f, 0.16f, 0, 153, 0);
    anyQuad(0.71f, 0.19f, 0.69f, 0.16f, 0.76f, 0.16f, 0.74f, 0.19f, 0, 204, 0);
    anyQuad(0.72f, 0.22f,0.70f, 0.19f, 0.75f, 0.19f, 0.73f, 0.22f, 128, 255, 0);
    anyQuad(0.71f, 0.10f, 0.71f, 0.0f, 0.73f, 0.0f, 0.73f, 0.10f, 102, 51, 0);
    anyQuad(0.73f, 0.10f, 0.73f, 0.0f, 0.74f, 0.0f, 0.74f, 0.10f, 153, 76, 0);
}

void cloudComponent(){
    Circle(-0.58f, 0.75f,  0.060f, 204, 204, 204);
    Circle(-0.5f, 0.82f,  0.068f, 204, 204, 204);
    Circle(-0.42f, 0.75f,  0.068f, 204, 204, 204);
    Circle(-0.5f, 0.72f,  0.07f, 204, 204, 204);
}
