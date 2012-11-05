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
#include <array>
#include <vector>

#include <iostream>
using namespace std;


using namespace DemoAttributes;

namespace  {
    //helper function
    void _generateTreeBranches(const Point3f& newPosition,
                               float startingLength,
                               float startingRotation,
                               const int currentDepth,
                               const int MAX_DEPTH,
                               const float ANGLE,
                               const float LENGTH_FACTOR);
    
    //generates a list of triangle points that represents sierpinkski triangle  
    void _generateSierpinskiTrianglePoints(const std::array<Point3f,3>& startTriangle,
                                            int currDepth,
                                            const int MAX_DEPTH,
                                            std::vector<Point3f>& results);
}

namespace Demo
{
    void renderFractalTree(const int MAX_DEPTH,
                           const float RELATIVE_ANGLE_DEG,
                           const float BRANCH_LENGTH_DECREASE_FACTOR)
    {
        const Point3f startPoint({0.0f,0.0f,0.0f});
        const Point3f endPoint({1.0f,0.0f,0.0f});
        const float rotation = 90.0f;
        glutWireSphere(0.05, 4, 4);
        _generateTreeBranches(startPoint,
                              1.0f,
                              rotation,
                              0,
                              MAX_DEPTH,
                              RELATIVE_ANGLE_DEG,
                              BRANCH_LENGTH_DECREASE_FACTOR);
    }
    
    void renderSierpinskiTriangle(const int MAX_DEPTH){
        const auto length = 3;
        const std::array<Point3f, 3> startingPoints = { Point3f({-length/2.0,0,0}),
                                                        Point3f({0,length,0}),
                                                        Point3f({length/2.0f,0,0,0})
                                                      };
        std::vector<Point3f> results;
        _generateSierpinskiTrianglePoints(startingPoints,0,MAX_DEPTH, results);
        cout << results.size() << endl;
        cout << "result.size % 3 == " << results.size() % 3 << endl;
        
        
        glBegin(GL_TRIANGLES);
        for(int i = 0; i < results.size(); i += 3){
            float colors[3][3] = { {1.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f}};
            glColor3fv(colors[random()%3]);
            glVertex3f(results[i].x, results[i].y,results[i].z);
            glVertex3f(results[i+1].x, results[i+1].y,results[i+1].z);
            glVertex3f(results[i+2].x, results[i+2].y,results[i+2].z);
        }
        glEnd();
    }
}


namespace  {
    
      //generates a list of triangle points that represents sierpinkski triangle
    void _generateSierpinskiTrianglePoints(const std::array<Point3f,3>& currentPoints,
                                           int currDepth,
                                           const int MAX_DEPTH,
                                           std::vector<Point3f>& data)
    {
        if(currDepth >= MAX_DEPTH) return;
        else{
            //compute the triangle that seperates current triangle into 3 equal triangle
            Point3f leftMidPoint = midpoint(currentPoints[0], currentPoints[1]);
            Point3f rightMidPoint = midpoint(currentPoints[1], currentPoints[2]);
            Point3f bottomMidPoint = midpoint(currentPoints[0], currentPoints[2]);
            
            data.push_back(leftMidPoint);
            data.push_back(rightMidPoint);
            data.push_back(bottomMidPoint);
            
            //generate overlap triangle for left side
            std::array<Point3f,3> leftTriangle = {currentPoints[0],leftMidPoint,bottomMidPoint};
            _generateSierpinskiTrianglePoints(leftTriangle, currDepth+1, MAX_DEPTH,data);
            
            //generate overlap triangle for top side
            std::array<Point3f,3> topTriangle = {leftMidPoint,currentPoints[1],rightMidPoint};
            _generateSierpinskiTrianglePoints(topTriangle, currDepth+1, MAX_DEPTH,data);
            
            //generate overlap triangle for right side
            std::array<Point3f,3> rightTriangle = {bottomMidPoint,rightMidPoint,currentPoints[2]};
            _generateSierpinskiTrianglePoints(rightTriangle, currDepth+1, MAX_DEPTH,data);
        }
        
    }
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
        if(depth < MAX_DEPTH){
            glColor3ub(188,142,142);
        }else if(depth == MAX_DEPTH){
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
