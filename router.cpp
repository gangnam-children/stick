//
//  router.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "router.h"

Router::Router() {
    responses.clear();
}

void Router::operator[] (Request req) {
    for (int i = 0; i < responses.size(); i++) {
        if (responses[i].isMatch(req.getRoute(), req.getMethod())) {
            responses[i].execute(req);
            break;
        }
    }
}

void Router::handle (Request req) {
    for (int i = 0; i < responses.size(); i++) {
        if (responses[i].isMatch(req.getRoute(), req.getMethod())) {
            responses[i].execute(req);
            break;
        }
    }
}

void Router::add(Response res) {
    responses.push_back(res);
}

Router* Router::instance = NULL;