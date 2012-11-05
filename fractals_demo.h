//
//  fractals_demo.h
//  RecursivePlay
//
//  Created by Dibash Chhetri on 10/30/12.
//  Copyright (c) 2012 Dibash Chhetri. All rights reserved.
//

#ifndef RecursivePlay_fractals_demo_h
#define RecursivePlay_fractals_demo_h



namespace Demo {
    void renderFractalTree(const int MAX_DEPTH,
                           const float RELATIVE_ANGLE_DEG,
                           const float BRANCH_LENGTH_DECREASE_FACTOR);
    
    void renderSierpinskiTriangle(const int MAX_DEPTH);
}

#endif
