//
//  main.cpp
//  RecursivePlay
//
//  Created by Dibash Chhetri on 10/29/12.
//  Copyright (c) 2012 Dibash Chhetri. All rights reserved.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <cmath>
#include <ctime>

#include "fractals_demo.h"
#include "utility.h"

using namespace std;


namespace{
    //fractals properties
    int MAX_DEPTH = 8;
    float CHILD_BRANCH_ANGLE = 25.0f;
    float BRANCH_LENGTH_DECREASE_FACTOR = 0.75f;
}

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, -10.0);
    Demo::renderFractalTree(MAX_DEPTH,CHILD_BRANCH_ANGLE,BRANCH_LENGTH_DECREASE_FACTOR);
	glutSwapBuffers();
   //glutPostRedisplay();
}


void changeSize(int w, int h){
    using namespace DemoAttributes;
    // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0){h = 1;}
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
	glLoadIdentity();
    
    if(DISPLAY_MODE == TWO_DIM){
        gluOrtho2D(0,WINDOW_WIDTH,0, WINDOW_HEIGHT);
    }else{ //3d move
        // Set the viewport to be the entire window
        glViewport(0, 0, w, h);
        // Set the correct perspective.
        gluPerspective(45,ratio,1,1000);
    }
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
    
}

void handleNormalKeyPress(unsigned char key, int x, int y) {
    enum {ESCAPE = 27};
    switch(key){
        case ESCAPE: std::exit(0); break;
    }
}

void pressKey(int key, int xx, int yy) {
    
	switch (key) {
		case GLUT_KEY_UP : break;
		case GLUT_KEY_DOWN :  break;
	}
}

void releaseKey(int key, int x, int y) {
    
	switch (key) {
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : break;
	}
}

void initOpenGL(){
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}
int main(int argc,char *argv[])
{
    srand( (unsigned int)time(0));
    // init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(150,150);
	glutInitWindowSize(800,600);
	glutCreateWindow("Recursive Play");
    
    initOpenGL();
    
	glutDisplayFunc(renderScene);
    
	glutReshapeFunc(changeSize);
    
    glutKeyboardFunc(handleNormalKeyPress);
    glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	// enter GLUT event processing cycle
	glutMainLoop();
    
    return 0;
}

