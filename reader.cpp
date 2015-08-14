//
//  reader.cpp
//  lightjson
//
//  Created by 정인중 on 2015. 8. 14..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#include <cstdlib>
#include "reader.h"
using namespace Json;

Reader::Reader() {
    index = 0;
    json = "";
    length = 0;
}

Value Reader::decode(string data) {
    json = data;
    index = 0;
    length = json.length();
    return parse();
}

Token Reader::nextToken() {
    char c = json[index];
    index++;
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            return TOKEN_NUMBER;
        case '{':
            return TOKEN_CURLY_OPEN;
        case '}':
            return TOKEN_CURLY_CLOSE;
        case '"':
            return TOKEN_STRING;
        case ',':
            return TOKEN_COMMA;
        case '[':
            return TOKEN_SQUARED_OPEN;
        case ']':
            return TOKEN_SQUARED_CLOSE;
        case ':':
            return TOKEN_COLON;
    }
    index--;
    if (json.substr(index, 5) == "false") {
        index += 5;
        return TOKEN_FALSE;
    } else if (json.substr(index, 4) == "true") {
        index += 4;
        return TOKEN_TRUE;
    } else if (json.substr(index, 4) == "null") {
        index += 4;
        return TOKEN_TRUE;
    }
    index++;
    return TOKEN_NONE;
}

Value Reader::parse() {
    bool complete = false;
    while (!complete) {
        if (index > length)
            break;
        
        switch (nextToken()) {
            case TOKEN_NUMBER:
                return parseNumber();
            case TOKEN_STRING:
                return parseString();
            case TOKEN_CURLY_OPEN:
                return parseObject();
            case TOKEN_SQUARED_OPEN:
                return parseArray();
            case TOKEN_TRUE:
                return true;
            case TOKEN_FALSE:
                return false;
            case TOKEN_NULL:
                return Value();
            default:
                return Value();
        }
    }
    
    return Value();
}

Value Reader::parseNumber() {
    index--;
    bool negative = json[index] == '-' ? true : false;
    string str = "";
    bool complete = false;
    while (!complete) {
        if (index >= length)
            break;
        
        char c = json[index];
        index++;
        switch (c) {
            case '{':
            case '}':
            case ':':
            case ',':
            case '[':
            case ']':
                index--;
                complete = true;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                str += c;
                break;
        }
    }
    int value = atoi(str.c_str());
    return negative ? -value : value;
}

Value Reader::parseString() {
    string str = "";
    bool complete = false;
    while (!complete) {
        if (index >= length)
            break;
        
        char c = json[index];
        index++;
        
        switch (c) {
            case '"':
                complete = true;
                break;
            default:
                str += c;
        }
    }
    if (!complete)
        return Value();
    
    return str;
}

Value Reader::parseArray() {
    Array ary;
    bool complete = false;
    while (!complete) {
        Token token = nextToken();
        if (token == TOKEN_SQUARED_CLOSE) {
            complete = true;
            break;
        } else if (token == TOKEN_NONE) {
            
        } else if (token == TOKEN_COMMA) {
            
        } else {
            index--;
            Value v = parse();
            ary.add(v);
        }
    }
    
    return ary;
}

Value Reader::parseObject() {
    Object obj;
    bool complete = false;
    while (!complete) {
        Token token = nextToken();
        if (token == TOKEN_CURLY_CLOSE) {
            complete = true;
            break;
        } else if (token == TOKEN_NONE) {
            //return Value();
        } else if (token == TOKEN_COMMA) {
            
        } else {
            Value key = parseString();
            if (key.type() == NIL)
                return Value();
            token = nextToken();
            if (token != TOKEN_COLON)
                return Value();
            
            Value val = parse();
            obj[key] = val;
        }
    }
    
    return obj;
}
