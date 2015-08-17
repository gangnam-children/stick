//
//  json.cpp
//  lightjson
//
//  Created by 정인중 on 2015. 8. 13..
//  Copyright (c) 2015년 InJung Chung. All rights reserved.
//

#include "json.h"
using namespace Json;

Object::Object() {
    
}

Object::Object(const Object& other) {
    table = other.table;
}

Value& Object::operator[](const string& key) {
    return table[key];
}

const Value& Object::operator[] (const string& key) const {
    return table.at(key);
}

Object& Object::operator=(const Object& other) {
    table = other.table;
    return *this;
}

map<string, Value>& Object::getTable() {
    return table;
}

Array::Array() {
    
}

Array::Array(const Array& other) {
    table = other.table;
}

Value& Array::operator[](const int& key) {
    return table.at(key);
}

const Value& Array::operator[] (const int& key) const {
    return table.at(key);
}

Array& Array::operator=(const Array& other) {
    table = other.table;
    return *this;
}

void Array::add(const Value& value) {
    table.push_back(value);
}

int Array::size() {
    return (int)table.size();
}

Value::Value() {
    valueType = NIL;
}

Value::Value(bool value) {
    bData = value;
    valueType = BOOL;
}

Value::Value(int value) {
    iData = value;
    valueType = INT;
}

Value::Value(double value) {
    dData = value;
    valueType = DOUBLE;
}

Value::Value(const char* value) {
    sData = value;
    valueType = STRING;
}

Value::Value(string& value) {
    sData = value;
    valueType = STRING;
}

Value::Value(Array& value) {
    aData = value;
    valueType = ARRAY;
}

Value::Value(Object& value) {
    oData = value;
    valueType = OBJECT;
}

Value::Value(const Value& other) {
    switch (other.valueType) {
        case BOOL:
            bData = other.bData;
            break;
        case INT:
            iData = other.iData;
            break;
        case DOUBLE:
            dData = other.dData;
            break;
        case STRING:
            sData = other.sData;
            break;
        case ARRAY:
            aData = other.aData;
            break;
        case OBJECT:
            oData = other.oData;
            break;
        case NIL:
            break;
    }
    valueType = other.valueType;
}

Value::operator bool() const {
    return bData;
}

Value::operator int() const {
    return iData;
}

Value::operator double() const {
    return dData;
}

Value::operator string() const {
    return sData;
}

Value::operator Array() const {
    return aData;
}

Value::operator Object() const {
    return oData;
}

Value& Value::operator=(const Value& other) {
    switch (other.valueType) {
        case BOOL:
            bData = other.bData;
            break;
        case INT:
            iData = other.iData;
            break;
        case DOUBLE:
            dData = other.dData;
            break;
        case STRING:
            sData = other.sData;
            break;
        case ARRAY:
            aData = other.aData;
            break;
        case OBJECT:
            oData = other.oData;
            break;
        case NIL:
            break;
    }
    valueType = other.valueType;
    
    return *this;
}

Value& Value::operator[](const char* key) {
    if (valueType != OBJECT)
        throw "JSON type error";
    
    return oData[key];
}

const Value& Value::operator[] (const char* key) const {
    if (valueType != OBJECT)
        throw "JSON type error";
    
    return oData[key];
}

Value& Value::operator[](const string& key) {
    if (valueType != OBJECT)
        throw "JSON type error";
    
    return oData[key];
}

const Value& Value::operator[] (const string& key) const {
    if (valueType != OBJECT)
        throw "JSON type error";
    
    return oData[key];
}

Value& Value::operator[](const int& key) {
    if (valueType != ARRAY)
        throw "JSON type error";
    
    return aData[key];
}

const Value& Value::operator[] (const int& key) const {
    if (valueType != ARRAY)
        throw "JSON type error";
    
    return aData[key];
}

double Value::toReal() const {
    return dData;
}
int Value::toInt() const {
    return iData;
}

bool Value::toBool() const {
    return bData;
}

string Value::toString() const {
    return sData;
}

Type Value::type() {
    return valueType;
}
