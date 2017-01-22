/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FColor.cpp
 * Author: terag
 * 
 * Created on December 12, 2016, 3:03 PM
 */

#include "FColor.hpp"

using namespace std;

FColor::FColor(int R, int G, int B, int A) :
    r(R), g(G), b(B), a(A)
{
    checkRange(r);
    checkRange(g);
    checkRange(b);
    checkRange(a);
}

void FColor::checkRange(int & value){
    if(value > 255){
        value = 255;
    } else
    if(value < 0){
        value = 0;
    }
}

FColor::FColor(const FColor& orig) :
    r(orig.r), g(orig.g), b(orig.b), a(orig.a)
{
}

FColor::~FColor() {
}

bool operator==(FColor const& left, FColor const& right){
    if(left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a){
        return true;
    } else {
        return false;
    }
}

bool operator!=(FColor const& left, FColor const& right){
    if(left.r == right.r && left.g == right.g && left.b == right.b && left.a == right.a){
        return false;
    } else {
        return true;
    }
}

FColor operator+(FColor const& left, FColor const& right){
    FColor color(left.r + right.r, left.g + right.g, left.b + right.g, color.a = left.a + right.a);
    return color;
}

FColor & FColor::operator+=(FColor const& right){
    this->r += right.r;
    checkRange(this->r);
    this->g += right.g;
    checkRange(this->g);
    this->b += right.b;
    checkRange(this->b);
    this->a += right.a;
    checkRange(this->a);
    return *this;
}