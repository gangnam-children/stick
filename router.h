//
//  router.h
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#ifndef __server__router__
#define __server__router__

#include <string>
using namespace std;

class Router {
private:
public:
    void response(string, string);
    void use(string, string, void*);
};

#endif /* defined(__server__router__) */
