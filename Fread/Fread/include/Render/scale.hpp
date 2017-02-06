/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scale.hpp
 * Author: emma
 *
 * Created on 6 février 2017, 18:42
 */

#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>

class scale {
private : 
    float absoluteTime = 1.f;
    int containerSize = 1000;
    int spacing = 100;
    unsigned int subdTimeLine;
    int containerOffsetX = 50;
    int containerOffsetY = 30;
    int eventOffsetY = 8;
    float constScale = 1.f;
    int windowContainerOffsetY;
    //variable related to the text of the timeline
    sf::Font font;
    std::vector<sf::Text> times;
    std::vector<sf::VertexArray> timeLines;
    
public : 
    scale();
    scale(float absoluteTime, int nbContainer, int containerSize, int windowContainerOffsetY);
    scale(float absoluteTime, int nbContainer, int containerSize,
          int spacing, int containerOffsetX, int containerOffsetY,
          int eventOffsetY, int windowContainerOffsetY);
    // getters
    float getScale();
    int getContainerSize();
    int getContainerOffsetX();
    int getContainerOffsetY();
    int getEventOffsetY();
    int getWindowContainerOffsetY();
    int getSpacing();
    // setters
    void setContainerSize(int containerSize);
    void setSpacing(int spacing);
    void setContainerOffsetX(int containerOffsetX);
    void setContainerOffsetY(int containerOffsetY);
    void setEventOffsetY(int eventOffsetY);
    void setWindowContainerOffsetY(int windowContainerOffsetY);
    //update
    void updateScale(int containerSize, int spacing, int containerOffsetX, 
                     int containerOffsetY, int eventOffsetY, int windowContainerOffsetY, int nbContainer);
    void updatePosition(int nbContainer);
    // draw
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

};
