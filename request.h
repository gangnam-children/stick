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
#include "json/json.h"
using namespace std;

class Request {
private:
    string route;
    string method;
    Json::Value parameter;
    Json::Value header;
    Json::Value body;
public:
    Request(string, string, Json::Value, Json::Value, Json::Value);
    string getRoute();
    string getMethod();
    Json::Value getParameter();
    Json::Value getHeader();
    Json::Value getBody();
};

#endif /* defined(__server__request__) */
