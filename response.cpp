//
//  response.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "response.h"
#include "GlobalFunc.h"
#include "lightjson.h"
#include "Log.h"

Response::Response(string route, string method, void(*func)(Request)) {
    this->route = route;
    this->method = method;
    this->handler = func;
}

string Response::getRoute() {
    return route;
}

bool Response::isMatch(Request& req) {
    if (req.getMethod() != this->method)
        return false;

    string myRoute = "";
    int realRouteSize = 0;
    vector<string> params;
    vector<string> routes = split(this->route, "/");
    for (string s : routes) {
        if (s[0] == ':') {
            params.push_back(s);
        } else {
            realRouteSize++;
            myRoute += s + "/";
        }
    }


    vector<string> routes2 = split(req.getRoute(), "/");

    for (int i = 0; i < realRouteSize; i++) {
        if (routes[i] != routes2[i])
            return false;
    }

    if (routes.size() != routes2.size())
        return false;

    for (int i = realRouteSize; i < routes2.size(); i++) {
        req.getParameter()[params[i - realRouteSize]] = routes2[i];
    }

    return true;
}

void Response::execute(Request req) {
    this->handler(req);
}
