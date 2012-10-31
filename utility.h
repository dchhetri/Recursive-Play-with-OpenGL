//
//  utility.h
//  RecursivePlay
//
//  Created by Dibash Chhetri on 10/30/12.
//  Copyright (c) 2012 Dibash Chhetri. All rights reserved.
//

#ifndef RecursivePlay_utility_h
#define RecursivePlay_utility_h


#include <initializer_list>

namespace DemoAttributes {
    
    //window properties
    const int WINDOW_WIDTH = 100;
    const int WINDOW_HEIGHT = 100;
    enum DisplayMode{ TWO_DIM, THREE_DIM };
    const bool DISPLAY_MODE = THREE_DIM;
    const float DEG_TO_RAD = 0.0174532925f;
    
    //utils
    struct Point3f{
        float x , y , z;
        Point3f(const std::initializer_list<float>& p);
    };
    
    void drawLine(float length);
    
}
#endif
