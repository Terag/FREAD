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
    sf::Color eventColor = sf::Color(60,60,60);
    eventType type;
    float ftStart, ftEnd = 0;
    int offsetY = 6;
    int offsetX;
    int containerOffsetY, containerID, windowContainerOffsetY = 0;
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