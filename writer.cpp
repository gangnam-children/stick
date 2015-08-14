//
//  writer.cpp
//  lightjson
//
//  Created by 정인중 on 2015. 8. 14..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#include "writer.h"

using namespace Json;

Writer::Writer() { }

string Writer::encode(Value value) {
    switch (value.type()) {
        case OBJECT:
            return encodeObject(value);
        case ARRAY:
            return encodeArray(value);
        case INT:
            return encodeInteger(value.toInt());
        case DOUBLE:
            return encodeInteger(value.toReal());
        case STRING:
            return encodeString(value.toString());
        case BOOL:
            return encodeBool(value.toBool());
        default:
            return "null";
    }
    
    return NULL;
}

string Writer::encodeObject(Object data) {
    string result = "{";
    map<string, Value> table = data.getTable();
    map<string, Value>::iterator iter;
    for (iter = table.begin(); iter != table.end(); ++iter) {
        result += "\"" + iter->first + "\":" + encode(iter->second) + ",";
    }
    result[result.size() - 1] = '}';
    
    return result;
}

string Writer::encodeArray(Array data) {
    string result = "[";
    for (int i = 0; i < data.size(); i++) {
        result += encode(data[i]) + ",";
    }
    result[result.size() - 1] = ']';
    return result;
}

string Writer::encodeInteger(int data) {
    return to_string(data);
}

string Writer::encodeString(string data) {
    return "\"" + data + "\"";
}

string Writer::encodeBool(bool data) {
    return data ? "true" : "false";
}
