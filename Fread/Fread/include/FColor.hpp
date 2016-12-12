/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FColor.hpp
 * Author: terag
 *
 * Created on December 12, 2016, 3:03 PM
 */

#ifndef FCOLOR_HPP
#define FCOLOR_HPP

#include <SFML/Graphics/Color.hpp>

class FColor {
public:

    FColor(int R = 0, int G = 0, int B = 0, int A = 0);
    FColor(const FColor& orig);
    
    FColor & operator+=(FColor const& right);

    virtual ~FColor();
    
    int r;
    int g;
    int b;
    int a;
    
private:
    void checkRange(int & value);
    
};

bool operator==(FColor const& left, FColor const& right);

bool operator!=(FColor const& left, FColor const& right);

FColor operator+(FColor const& left, FColor const& right);


#endif /* FCOLOR_HPP */

