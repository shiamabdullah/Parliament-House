#include "shapes.h"

void blank(){
}

void sunComponent()
{
    Circle(0.8f, 0.8f, 0.09f, 255, 255, 0);
}


void moonComponent()
{
    Circle(0.8f, 0.8f,  0.09f, 245, 245, 245);
}

void treeComponent(){
    anyQuad(0.69f, 0.13f, 0.67f, 0.10f, 0.78f, 0.10f, 0.76f, 0.13f, 0, 102, 51);
    anyQuad(0.70f, 0.16f, 0.68f, 0.13f, 0.77f, 0.13f, 0.75f, 0.16f, 0, 153, 0);
    anyQuad(0.71f, 0.19f, 0.69f, 0.16f, 0.76f, 0.16f, 0.74f, 0.19f, 0, 204, 0);
    anyQuad(0.72f, 0.22f,0.70f, 0.19f, 0.75f, 0.19f, 0.73f, 0.22f, 128, 255, 0);
    anyQuad(0.71f, 0.10f, 0.71f, 0.0f, 0.73f, 0.0f, 0.73f, 0.10f, 102, 51, 0);
    anyQuad(0.73f, 0.10f, 0.73f, 0.0f, 0.74f, 0.0f, 0.74f, 0.10f, 153, 76, 0);
}
