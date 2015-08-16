//
//  GlobalFunc.h
//  server
//
//  Created by 정인중 on 2015. 8. 14..
//  Copyright (c) 2015년 강남어린이들. All rights reserved.
//

#ifndef server_GlobalFunc_h
#define server_GlobalFunc_h

#include <vector>
#include <string>
using namespace std;

vector<std::string> split(const std::string & str, const std::string & delimiters) {
    vector<std::string> v;
    typename std::string::size_type start = 0;
    auto pos = str.find_first_of(delimiters, start);
    while (pos != std::string::npos) {
        if (pos != start) // ignore empty tokens
            v.emplace_back(str, start, pos - start);
        start = pos + 1;
        pos = str.find_first_of(delimiters, start);
    }
    if (start < str.length()) // ignore trailing delimiter
        v.emplace_back(str, start, str.length() - start);
    return v;
}

#endif
