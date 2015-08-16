//
//  request.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "request.h"

Request::Request(string route, string method, Json::Object parameter, Json::Object body) {
    this->route = route;
    this->method = method;
    this->parameter = parameter;
    this->body = body;
}

string Request::getRoute() {
    return route;
}

string Request::getMethod() {
    return method;
}

Json::Object& Request::getParameter() {
    return parameter;
}

Json::Object Request::getBody() {
    return body;
}
