//
//  response.h
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#ifndef __server__response__
#define __server__response__

#include <string>
#include "request.h"
using namespace std;

class Response {
private:
    string route;
    string method;
    void(*handler)(Request);
public:
    Response(string, string, void(*)(Request));
    string getRoute();
    bool isMatch(Request&);
    void execute(Request);
};


#endif /* defined(__server__response__) */
