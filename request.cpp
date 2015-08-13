//
//  request.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "request.h"

Request::Request(string route, string method, Json::Value parameter, Json::Value header, Json::Value body) {
    this->route = route;
    this->method = method;
    this->parameter = parameter;
    this->header = header;
    this->body = body;
}

string Request::getRoute() {
    return route;
}

string Request::getMethod() {
    return method;
}

Json::Value Request::getParameter() {
    return parameter;
}

Json::Value Request::getHeader() {
    return header;
}

Json::Value Request::getBody() {
    return body;
}
