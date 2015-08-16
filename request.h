//
//  request.h
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#ifndef __server__request__
#define __server__request__

#include <string>
#include "lightjson.h"
using namespace std;

class Request {
private:
    string route;
    string method;
    Json::Object parameter;
    Json::Object body;
public:
    Request();
    Request(string, string, Json::Object, Json::Object);
    string getRoute();
    string getMethod();
    Json::Object& getParameter();
    Json::Object getBody();
};

#endif /* defined(__server__request__) */
