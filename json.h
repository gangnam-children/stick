//
//  json.h
//  lightjson
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#ifndef __lightjson__
#define __lightjson__

#include <string>
#include <map>
#include <vector>
using namespace std;

namespace Json {
    class Value;
    
    enum Token {
        TOKEN_NONE,
        TOKEN_CURLY_OPEN,
        TOKEN_CURLY_CLOSE,
        TOKEN_SQUARED_OPEN,
        TOKEN_SQUARED_CLOSE,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_STRING,
        TOKEN_NUMBER,
        TOKEN_TRUE,
        TOKEN_FALSE,
        TOKEN_NULL
    };
    
    enum Type {
        BOOL,
        INT,
        DOUBLE,
        STRING,
        ARRAY,
        OBJECT,
        NIL
    };
    
    class Object {
    private:
        map<string, Value> table;
    public:
        Object();
        Object(const Object&);
        
        Value& operator[](const string&);
        const Value& operator[] (const string&) const;
        Object& operator=(const Object&);
        map<string, Value>& getTable();
    };
    
    class Array {
    private:
        vector<Value> table;
    public:
        Array();
        Array(const Array&);
        
        Value& operator[](const int&);
        const Value& operator[] (const int&) const;
        Array& operator=(const Array&);
        void add(const Value&);
        int size();
    };
    
    class Value {
    private:
        bool bData;
        int iData;
        double dData;
        string sData;
        Array aData;
        Object oData;
        
        Type valueType;
    public:
        Value();
        Value(bool);
        Value(int);
        Value(double);
        Value(const char*);
        Value(string&);
        Value(Array&);
        Value(Object&);
        Value(const Value&);
        
        operator bool() const;
        operator int() const;
        operator double() const;
        operator string() const;
        operator Array() const;
        operator Object() const;
        Value& operator=(const Value&);
        Value& operator[](const char*);
        const Value& operator[] (const char*) const;
        Value& operator[](const string&);
        const Value& operator[] (const string&) const;
        Value& operator[](const int&);
        const Value& operator[] (const int&) const;
        
        double toReal() const;
        int toInt() const;
        bool toBool() const;
        string toString() const;
        
        Type type();
    };
}

#endif /* defined(__lightjson__) */
