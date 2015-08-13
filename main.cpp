//
//  main.cpp
//  server
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#include <iostream>
#include "json/json.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Json::Value root;
    root["z"] = 123;
    root["x"] = "12";
    std::cout << root["z"] <<" " << root["x"] << std::endl;
    return 0;
}
