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
#include <vector>
#include "response.h"
#include "request.h"
using namespace std;

class Router {
private:
    vector<Response> responses;
    static Router* instance;
    
    Router();
public:
    void operator[] (Request);
    void handle(Request);
    void add(Response);
    
    static Router* getInstance() {
        if (instance == NULL)
            instance = new Router();
        
        return instance;
    }
};

#endif /* defined(__server__router__) */
