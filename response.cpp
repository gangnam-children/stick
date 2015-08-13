//
//  response.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "response.h"

Response::Response(string route, string method, void(*func)(Request)) {
    this->route = route;
    this->method = method;
    this->handler = func;
}

bool Response::isMatch(string route, string method) {
    return (this->route == route && this->method == method);
}

void Response::execute(Request req) {
    this->handler(req);
}