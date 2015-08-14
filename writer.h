//
//  writer.h
//  lightjson
//
//  Created by 정인중 on 2015. 8. 14..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#ifndef __lightjson__writer__
#define __lightjson__writer__

#include "json.h"

namespace Json {
    class Writer {
    private:
        string encodeObject(Object);
        string encodeArray(Array);
        string encodeInteger(int);
        string encodeString(string);
        string encodeBool(bool);
    public:
        Writer();
        Writer(Value);
        
        string encode(Value);
    };
}

#endif /* defined(__lightjson__writer__) */
