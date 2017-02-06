/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scale.hpp
 * Author: Emma et Jerome 
 *
 * Created on 6 février 2017, 18:42
 */

#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>

class scale {
private : 
    // the execution time of the whole trace
    float absoluteTime = 1.f;
    // the size in pixel we wants the container to have on the interface
    int containerSize = 1000;
    // the number of pixels between each line of the timeline
    int spacing = 100;
    //number of subdivision of the timeline
    unsigned int subdTimeLine;
    // the offset of the x-axis where starts the 0 of the timeline (and the containers)
    int containerOffsetX = 50;
    // the space between each containers 
    int containerOffsetY = 30;
    // the height of all the rectangles representing the events on the containers
    int eventOffsetY = 8;
    // constScale = containersize/absoluteTime 
    float constScale = 1.f;
    // determines where on the y-axis will be drawn the containers and the timeline 
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