//
//  router.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include "router.h"

void Router::operator[] (Request req) {
    
}

void use(string route, string method, void(*function)(Request req)) {
    Response res = new Response(route, method, *function);
    responses.push_back();
}

Router* Router::instance = NULL;