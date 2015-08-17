//
//  reader.h
//  lightjson
//
//  Created by 정인중 on 2015. 8. 14..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#ifndef __lightjson__reader__
#define __lightjson__reader__

#include "json.h"

namespace Json {
    class Reader {
    private:
        int index;
        string json;
        unsigned long length;
        
        Token nextToken();
        Value parse();
        Value parseNumber();
        Value parseDouble();
        Value parseString();
        Value parseArray();
        Value parseObject();
    public:
        Reader();
        Value decode(string);
    };
}

#endif /* defined(__lightjson__reader__) */
