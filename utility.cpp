//
//  utility.cpp
//  RecursivePlay
//
//  Created by Dibash Chhetri on 10/30/12.
//  Copyright (c) 2012 Dibash Chhetri. All rights reserved.
//

#include "utility.h"
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <cmath>

namespace DemoAttributes{
    
    void drawLine(float length){
        glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(length,0.0f,0.0f);
        glEnd();
    }
    

    Point3f::Point3f(const std::initializer_list<float>& p)
    :x(0),y(0),z(0)
    {
        auto itr = p.begin();
        if(itr != p.end()) x = *itr;
        ++itr;
        if(itr != p.end()) y = *itr;
        ++itr;
        if(itr != p.end()) z = *itr;
        
    }
    
    float pointDistance(const Point3f& p1, const Point3f& p2){
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        float dz = p2.z - p1.z;
        return std::sqrt( dx*dx + dy*dy + dz*dz);
    }
    
    Point3f midpoint(const Point3f& p1, const Point3f& p2){
        return {(p1.x+p2.x)/2.0f, (p1.y+p2.y)/2.0f};
    }
    
}