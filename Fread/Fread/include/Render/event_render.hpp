/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   event_render.hpp
 * Author: Emma et Jerome 
 *
 * Created on 6 février 2017, 18:25
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../FObjet.hpp"

class event_render : public sf::Drawable {
    
private:
    // color of the rectangle that represents the event
    sf::Color eventColor = sf::Color(60,60,60);
    // type of the event (COMPUTE, SEND or WAIT), which determines the color
    eventType type;
    // the actual lapse of time that takes the event in the trace, these values will never change
    float ftStart, ftEnd = 0;
    // the height of the rectangle drawn on the trace
    int offsetY = 6;
    // the offset of the drawn containers on the x-axis, so that the rectangle can be drawn at the right place on the timeline
    int offsetX;
    //the space between the containers
    int containerOffsetY= 0;
    //the id of the containers, so that the rectangle is drawn on the right one
    int containerID =0;
    // the offset that determines where the containers are drawn on the window (here it will be on the half bottom of the window)
    int windowContainerOffsetY = 0;
    // the vertices of the rectangle
    sf::VertexArray rectangles = sf::VertexArray(sf::Quads, 4);
    
public:
    //constructor & destructor
    event_render();
    event_render(eventType type, float tSStart, float tSEnd,
                 float scale, int containerOffsetY, int containerID,
                 int offsetY, int containerOffsetX, int windowContainerOffsetY);
    ~event_render();
    //setters
    void setColor();
    //getters
    eventType getType();
    sf::Color getColor();
    std::string getTypeString();
    //update
    void updatePosition(int newScale, int containerOffsetY, int offsetX,int offsetY);
    //draw
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};