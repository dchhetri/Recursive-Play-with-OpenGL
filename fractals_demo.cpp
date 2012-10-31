//
//  fractals_demo.cxx
//  RecursivePlay
//
//  Created by Dibash Chhetri on 10/30/12.
//  Copyright (c) 2012 Dibash Chhetri. All rights reserved.
//

#ifndef RecursivePlay_fractals_demo_cxx
#define RecursivePlay_fractals_demo_cxx

#include "fractals_demo.h"
#include "utility.h"
#include <GLUT/GLUT.h>
#include <cmath>

using namespace DemoAttributes;

namespace  {
    //helper function
    void _generateTreeBranches(const Point3f& newPosition,
                               float length,
                               float rotation,
                               const int currDepth,
                               const int MAX_DEPTH,
                               const float ANGLE,
                               const float LENGTH_FACTOR);
}

namespace Demo
{
    void renderFractalTree(const int MAX_DEPTH,
                           const float RELATIVE_ANGLE_DEG,
                           const float BRANCH_LENGTH_DECREASE_FACTOR)
    {
        Point3f startPoint({0.0f,0.0f,0.0f});
        Point3f endPoint({1.0f,0.0f,0.0f});
        float rotation = 90.0f;
        glutWireSphere(0.05, 4, 4);
        _generateTreeBranches(startPoint,1.0f,rotation,0,MAX_DEPTH,RELATIVE_ANGLE_DEG,BRANCH_LENGTH_DECREASE_FACTOR);
    }
}


namespace  {
    void _generateTreeBranches(const Point3f& newPosition,
                               float length,
                               float rotation,
                               const int depth,
                               const int MAX_DEPTH,
                               const float RELATIVE_ANGLE_DEG,
                               const float BRANCH_LENGTH_DECREASE_FACTOR)
    {
        if(depth > MAX_DEPTH) return;
        
        //just some coloring
        if(depth == 0){
            glColor3f(1.0f,1.0f,1.0f);
        }else if(depth == 1){
            glColor3f(1.0f,0.0f,0.0f);
        }else{
            glColor3f(0.0f,1.0f,0.0f);
        }
        
        glPushMatrix();
        glTranslatef(newPosition.x,newPosition.y,newPosition.z);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        drawLine(length);
        glLoadIdentity();
        glPopMatrix();
        
        //calculate new end point
        const float newLength = length * BRANCH_LENGTH_DECREASE_FACTOR;
        float newX =  newPosition.x + length *cos(rotation*DEG_TO_RAD);
        float newY =  newPosition.y + length *sin(rotation*DEG_TO_RAD);
        
        Point3f nextPosition = {newX,newY,newPosition.z};
        //calculate relative rotation
        float leftRotation  =  RELATIVE_ANGLE_DEG + rotation;
        float rightRotation = -RELATIVE_ANGLE_DEG + rotation;
        //generate left/right branches
        _generateTreeBranches(nextPosition,newLength,leftRotation,depth+1,MAX_DEPTH,RELATIVE_ANGLE_DEG,BRANCH_LENGTH_DECREASE_FACTOR);
        _generateTreeBranches(nextPosition,newLength,rightRotation,depth+1,MAX_DEPTH,RELATIVE_ANGLE_DEG,BRANCH_LENGTH_DECREASE_FACTOR);
        
    }
    
}

#endif
